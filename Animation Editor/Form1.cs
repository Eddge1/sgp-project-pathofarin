﻿using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Linq;
using SGP;
using System.Diagnostics;
namespace Animation_Editor
{
    public struct CFrame
    {
        //Render
        Rectangle rRender;

        public Rectangle RenderRect
        {
            get { return rRender; }
            set { rRender = value; }
        }

        Rectangle rCollision;

        public Rectangle CollisionRect
        {
            get { return rCollision; }
            set { rCollision = value; }
        }

        Point anchor;

        public Point Anchor
        {
            get { return anchor; }
            set { anchor = value; }
        }

        decimal dDuration;

        public decimal Duration
        {
            get { return dDuration; }
            set { dDuration = value; }
        }


        string szEventID;

        public string EventID
        {
            get { return szEventID; }
            set { szEventID = value; }
        }
    }

    public struct CAnimation
    {
        List<CFrame> lFrameList;
        string szAnimationName;
        bool bAnimationLooping;

        public void Initialize()
        {
            lFrameList = new List<CFrame>();
            szAnimationName = "";
            bAnimationLooping = false;
        }

        public bool AnimationLooping
        {
            get { return bAnimationLooping; }
            set { bAnimationLooping = value; }
        }

        public List<CFrame> FrameList
        {
            get { return lFrameList; }
            set { lFrameList = value; }
        }

        public string AnimationName
        {
            get { return szAnimationName; }
            set { szAnimationName = value; }
        }

    }


    public partial class Form1 : Form
    {
        bool doOnce = true;
        bool looping = true;
        bool bMouseDown = false;
        bool bPlaying = false;
        int nImageID = -1;
        string szPath;
        string szFileName = "";
        string szTextureName = "";
        List<CAnimation> AnimationSet = new List<CAnimation>();
        List<CFrame> tempFrameList = new List<CFrame>();
        CFrame workingFrame = new CFrame();
        CSGP_Direct3D D3D;
        CSGP_TextureManager TM;
        Stopwatch sw = new Stopwatch();


        public Form1()
        {
            InitializeComponent();

            D3D = CSGP_Direct3D.GetInstance();
            TM = CSGP_TextureManager.GetInstance();
        }

        public bool Looping
        {
            get { return looping; }
            set { looping = value; }
        }

        public void Initialize()
        {
            szPath = Environment.CurrentDirectory + "\\..\\assets\\Graphics\\Sprites";
            szFileName = "";
            szTextureName = "";


            listBox_AnimationList.Items.Clear();
            listBox_FrameList.Items.Clear();
            AnimationSet.Clear();


            D3D.Initialize(splitContainer1.Panel2, false);
            D3D.AddRenderTarget(pictureBox_AnimationPreview);


            if (nImageID != -1)
                TM.UnloadTexture(nImageID);

            nImageID = -1;

            TM.Initialize(D3D.Device, D3D.Sprite);
        }

        public new void Update()
        {
            if (bPlaying == true)
            {
                sw.Start();
                CFrame playFrame = (CFrame)listBox_FrameList.SelectedItem;
                if (sw.ElapsedMilliseconds > playFrame.Duration * 1000)
                {
                    if (listBox_FrameList.SelectedIndex > -1)
                    {
                        if (listBox_FrameList.SelectedIndex == listBox_FrameList.Items.Count - 1)
                            listBox_FrameList.SelectedIndex = 0;
                        else
                            listBox_FrameList.SelectedIndex++;
                        sw.Restart();
                    }
                }
            }

        }

        public void Render()
        {
            D3D.Clear(splitContainer1.Panel2, Color.Magenta);
            D3D.DeviceBegin();
            D3D.SpriteBegin();

            if (nImageID != -1)
            {
                TM.Draw(nImageID, splitContainer1.Panel2.AutoScrollPosition.X, splitContainer1.Panel2.AutoScrollPosition.Y);
            }


            for (int i = 0; i < listBox_FrameList.Items.Count; i++)
            {
                CFrame temp = (CFrame)listBox_FrameList.Items[i];
                D3D.DrawHollowRect(temp.RenderRect, Color.FromArgb(255, 255, 255, 0), 1);
                D3D.DrawHollowRect(temp.CollisionRect, Color.FromArgb(255, 0, 255, 255), 1);
                Rectangle largePoint = new Rectangle();
                largePoint.X = temp.Anchor.X - 2;
                largePoint.Y = temp.Anchor.Y - 2;
                largePoint.Width = 4;
                largePoint.Height = 4;
                D3D.DrawRect(largePoint, Color.FromArgb(255, 0, 0, 255));
            }

            Rectangle largeWorkingPoint = new Rectangle();
            largeWorkingPoint.X = workingFrame.Anchor.X - 2;
            largeWorkingPoint.Y = workingFrame.Anchor.Y - 2;
            largeWorkingPoint.Width = 4;
            largeWorkingPoint.Height = 4;
            D3D.DrawHollowRect(workingFrame.RenderRect, Color.FromArgb(255, 0, 0, 0), 1);
            D3D.DrawHollowRect(workingFrame.CollisionRect, Color.FromArgb(255, 0, 255, 255), 1);
            D3D.DrawRect(largeWorkingPoint, Color.FromArgb(255, 0, 0, 255));


            D3D.SpriteEnd();
            D3D.DeviceEnd();
            D3D.Present();


            D3D.Clear(pictureBox_AnimationPreview, Color.Magenta);
            D3D.DeviceBegin();
            D3D.SpriteBegin();

            if (nImageID != -1)
            {
                if (listBox_FrameList.SelectedIndex > -1)
                {
                    CFrame PreviewRect = (CFrame)listBox_FrameList.SelectedItem;
                    TM.Draw(nImageID, pictureBox_AnimationPreview.ClientRectangle.Width / 2 - PreviewRect.RenderRect.Width / 2,
                        pictureBox_AnimationPreview.ClientRectangle.Height / 2 - PreviewRect.RenderRect.Height / 2, 1.0f, 1.0f, PreviewRect.RenderRect);
                }
            }

            D3D.SpriteEnd();
            D3D.DeviceEnd();
            D3D.Present();

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Initialize();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }

        private void saveAnimationSetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int nTempBool = 0;

            if (szFileName == "" && File.Exists(szFileName) == false)
            {
                saveAsToolStripMenuItem_Click(sender, e);
            }
            else
            {
                XElement xRoot = new XElement("Animation_Data");
                for (int j = 0; j < listBox_AnimationList.Items.Count; j++)
                {
                    CAnimation cTemp = (CAnimation)listBox_AnimationList.Items[j];
                    XElement xInfo = new XElement("Animation_Info");
                    XAttribute xName = new XAttribute("Name", cTemp.AnimationName);
                    XAttribute xFrameCount = new XAttribute("Frames", cTemp.FrameList.Count);  //Change this to the actual size of the Frame vector later

                    if (cTemp.AnimationLooping == true)
                    {
                        nTempBool = 1;
                    }
                    else
                    {
                        nTempBool = 0;
                    }
                    XAttribute xRepeat = new XAttribute("repeat", nTempBool);
                    XAttribute xTexture = new XAttribute("Texture", szTextureName);

                    xInfo.Add(xName);
                    xInfo.Add(xFrameCount);
                    xInfo.Add(xRepeat);
                    xInfo.Add(xTexture);


                    xRoot.Add(xInfo);


                    XElement xFrameData = new XElement("Frame_Data");

                    for (int i = 0; i < cTemp.FrameList.Count; i++)
                    {
                        XElement xRender = new XElement("Render");
                        XAttribute xPosX = new XAttribute("posX", cTemp.FrameList[i].RenderRect.X);
                        XAttribute xPosY = new XAttribute("posY", cTemp.FrameList[i].RenderRect.Y);
                        XAttribute xWidth = new XAttribute("Width", cTemp.FrameList[i].RenderRect.Width);
                        XAttribute xHeight = new XAttribute("Height", cTemp.FrameList[i].RenderRect.Height);
                        XAttribute xAnchorX = new XAttribute("anchorX", cTemp.FrameList[i].RenderRect.X - cTemp.FrameList[i].Anchor.X);
                        XAttribute xAnchorY = new XAttribute("anchorY", cTemp.FrameList[i].RenderRect.Y - cTemp.FrameList[i].Anchor.Y);
                        XAttribute xDuration = new XAttribute("Duration", cTemp.FrameList[i].Duration);
                        XAttribute xEvent = new XAttribute("Event", cTemp.FrameList[i].EventID);

                        xRender.Add(xPosX);
                        xRender.Add(xPosY);
                        xRender.Add(xWidth);
                        xRender.Add(xHeight);
                        xRender.Add(xAnchorX);
                        xRender.Add(xAnchorY);
                        xRender.Add(xDuration);
                        xRender.Add(xEvent);

                        xFrameData.Add(xRender);

                        XElement xCollision = new XElement("ActiveCollision");
                        XAttribute xCPosX = new XAttribute("posX", cTemp.FrameList[i].RenderRect.X - cTemp.FrameList[i].CollisionRect.X);
                        XAttribute xCPosY = new XAttribute("posY", cTemp.FrameList[i].RenderRect.Y - cTemp.FrameList[i].CollisionRect.Y);
                        XAttribute xCWidth = new XAttribute("Width", cTemp.FrameList[i].CollisionRect.Width);
                        XAttribute xCHeight = new XAttribute("Height", cTemp.FrameList[i].CollisionRect.Height);

                        xCollision.Add(xCPosX);
                        xCollision.Add(xCPosY);
                        xCollision.Add(xCWidth);
                        xCollision.Add(xCHeight);

                        xFrameData.Add(xCollision);

                    }
                    xInfo.Add(xFrameData);
                }
                xRoot.Save(szFileName);

            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            string tempPath = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Data\\Animations");
            dlg.InitialDirectory = tempPath;
            dlg.Filter = "All Files|*.*|XML Files|*.xml";
            dlg.FilterIndex = 2;

            int nTempBool = 0;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                XElement xRoot = new XElement("Animation_Data");
                for (int j = 0; j < listBox_AnimationList.Items.Count; j++)
                {
                    CAnimation cTemp = (CAnimation)listBox_AnimationList.Items[j];
                    XElement xInfo = new XElement("Animation_Info");
                    XAttribute xName = new XAttribute("Name", cTemp.AnimationName);
                    XAttribute xFrameCount = new XAttribute("Frames", cTemp.FrameList.Count);  //Change this to the actual size of the Frame vector later

                    if (cTemp.AnimationLooping == true)
                    {
                        nTempBool = 1;
                    }
                    else
                    {
                        nTempBool = 0;
                    }
                    XAttribute xRepeat = new XAttribute("repeat", nTempBool);
                    XAttribute xTexture = new XAttribute("Texture", szTextureName);

                    xInfo.Add(xName);
                    xInfo.Add(xFrameCount);
                    xInfo.Add(xRepeat);
                    xInfo.Add(xTexture);


                    xRoot.Add(xInfo);


                    XElement xFrameData = new XElement("Frame_Data");

                    for (int i = 0; i < cTemp.FrameList.Count; i++)
                    {
                        XElement xRender = new XElement("Render");
                        XAttribute xPosX = new XAttribute("posX", cTemp.FrameList[i].RenderRect.X);
                        XAttribute xPosY = new XAttribute("posY", cTemp.FrameList[i].RenderRect.Y);
                        XAttribute xWidth = new XAttribute("Width", cTemp.FrameList[i].RenderRect.Width);
                        XAttribute xHeight = new XAttribute("Height", cTemp.FrameList[i].RenderRect.Height);
                        XAttribute xAnchorX = new XAttribute("anchorX", cTemp.FrameList[i].RenderRect.X - cTemp.FrameList[i].Anchor.X);
                        XAttribute xAnchorY = new XAttribute("anchorY", cTemp.FrameList[i].RenderRect.Y - cTemp.FrameList[i].Anchor.Y);
                        XAttribute xDuration = new XAttribute("Duration", cTemp.FrameList[i].Duration);
                        XAttribute xEvent = new XAttribute("Event", cTemp.FrameList[i].EventID);

                        xRender.Add(xPosX);
                        xRender.Add(xPosY);
                        xRender.Add(xWidth);
                        xRender.Add(xHeight);
                        xRender.Add(xAnchorX);
                        xRender.Add(xAnchorY);
                        xRender.Add(xDuration);
                        xRender.Add(xEvent);

                        xFrameData.Add(xRender);

                        XElement xCollision = new XElement("ActiveCollision");
                        XAttribute xCPosX = new XAttribute("posX", cTemp.FrameList[i].RenderRect.X - cTemp.FrameList[i].CollisionRect.X);
                        XAttribute xCPosY = new XAttribute("posY", cTemp.FrameList[i].RenderRect.Y - cTemp.FrameList[i].CollisionRect.Y);
                        XAttribute xCWidth = new XAttribute("Width", cTemp.FrameList[i].CollisionRect.Width);
                        XAttribute xCHeight = new XAttribute("Height", cTemp.FrameList[i].CollisionRect.Height);

                        xCollision.Add(xCPosX);
                        xCollision.Add(xCPosY);
                        xCollision.Add(xCWidth);
                        xCollision.Add(xCHeight);

                        xFrameData.Add(xCollision);

                    }
                    xInfo.Add(xFrameData);
                }
                szFileName = dlg.FileName;
                xRoot.Save(szFileName);
            }

        }

        private void loadSpriteSheetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            string tempPath = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Graphics\\Sprites");
            dlg.InitialDirectory = tempPath;
            dlg.Filter = "All Files|*.*";
            dlg.FilterIndex = 2;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                if (nImageID != -1)
                    TM.UnloadTexture(nImageID);

                nImageID = TM.LoadTexture(dlg.FileName);
                Size tempSize = new Size();
                tempSize.Width = TM.GetTextureWidth(nImageID);
                tempSize.Height = TM.GetTextureHeight(nImageID);
                splitContainer1.Panel2.AutoScrollMinSize = tempSize;

            }

        }

        private void button_AddFrame_Click(object sender, EventArgs e)
        {
            if (listBox_AnimationList.Items.Count > 0)
            {
                CAnimation cAnim = (CAnimation)listBox_AnimationList.Items[listBox_AnimationList.SelectedIndex];


                //tempFrameList.Add(tempFrame);
                listBox_FrameList.Items.Add(workingFrame);
                cAnim.FrameList.Add(workingFrame);
                listBox_AnimationList.Items[listBox_AnimationList.SelectedIndex] = cAnim;
                listBox_AnimationList.SelectedIndex = listBox_AnimationList.Items.Count - 1;
                workingFrame = new CFrame();

            }
        }

        private void splitContainer1_Panel2_Resize(object sender, EventArgs e)
        {
            if (doOnce == false)
            {
                D3D.Resize(splitContainer1.Panel2, splitContainer1.Panel2.ClientSize.Width, splitContainer1.Panel2.ClientSize.Height, false);
            }
            doOnce = false;

        }

        private void newAnimationSetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Initialize();
        }

        private void button_AddAnimation_Click(object sender, EventArgs e)
        {
            CAnimation tempAnimation = new CAnimation();
            tempAnimation.Initialize();
            tempAnimation.AnimationName = textBox_AnimationName.Text;
            tempAnimation.AnimationLooping = checkBox_AnimationLooping.Checked;
            listBox_FrameList.Items.Clear();

            //AnimationSet.Add(tempAnimation);
            listBox_AnimationList.Items.Add(tempAnimation);
            listBox_AnimationList.SelectedIndex = listBox_AnimationList.Items.Count - 1;
        }

        private void openAnimationSetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            string tempPath = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Data\\Animations");
            dlg.InitialDirectory = tempPath;
            dlg.Filter = "All Files|*.*";
            dlg.FilterIndex = 2;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                Initialize();
                CAnimation tempAnim = new CAnimation();
                tempAnim.Initialize();
                CFrame tempFrame = new CFrame();

                XElement xRoot = XElement.Load(dlg.FileName);

                IEnumerable<XElement> xInfo = xRoot.Elements("Animation_Info");
                foreach (XElement x in xInfo)
                {
                    tempAnim = new CAnimation();
                    tempAnim.Initialize();
                    XAttribute xName = x.Attribute("Name");
                    XAttribute xFrames = x.Attribute("Frames");
                    XAttribute xRepeat = x.Attribute("repeat");
                    XAttribute xTexture = x.Attribute("Texture");

                    tempAnim.AnimationName = xName.Value;
                    if (Convert.ToInt32(xRepeat.Value) == 0)
                    {
                        tempAnim.AnimationLooping = false;
                    }
                    else
                    {
                        tempAnim.AnimationLooping = true;
                    }
                    szTextureName = xTexture.Value;

                    IEnumerable<XElement> xFrameData = x.Elements("Frame_Data");
                    foreach (XElement j in xFrameData)
                    {
                        IEnumerable<XElement> xRender = xFrameData.Elements();
                        foreach (XElement r in xRender)
                        {
                            if (r.Name == "Render")
                            {
                                XAttribute xPosX = r.Attribute("posX");
                                XAttribute xPosY = r.Attribute("posY");
                                XAttribute xWidth = r.Attribute("Width");
                                XAttribute xHeight = r.Attribute("Height");
                                XAttribute xAnchorX = r.Attribute("anchorX");
                                XAttribute xAnchorY = r.Attribute("anchorY");
                                XAttribute xDuration = r.Attribute("Duration");
                                XAttribute xEvent = r.Attribute("Event");

                                Rectangle tempRect = new Rectangle();
                                tempRect.X = Convert.ToInt32(xPosX.Value);
                                tempRect.Y = Convert.ToInt32(xPosY.Value);
                                tempRect.Width = Convert.ToInt32(xWidth.Value);
                                tempRect.Height = Convert.ToInt32(xHeight.Value);

                                Point tempPoint = new Point();
                                tempPoint.X = Convert.ToInt32(xAnchorX.Value) + tempRect.X;
                                tempPoint.Y = Convert.ToInt32(xAnchorY.Value) + tempRect.Y;

                                tempFrame.RenderRect = tempRect;
                                tempFrame.Anchor = tempPoint;
                                tempFrame.Duration = Convert.ToDecimal(xDuration.Value);
                                tempFrame.EventID = xEvent.Value;
                            }
                            else if (r.Name == "ActiveCollision")
                            {
                                XAttribute xPosX = r.Attribute("posX");
                                XAttribute xPosY = r.Attribute("posY");
                                XAttribute xWidth = r.Attribute("Width");
                                XAttribute xHeight = r.Attribute("Height");

                                Rectangle tempRect = new Rectangle();
                                tempRect.X = Convert.ToInt32(xPosX.Value) + tempFrame.RenderRect.X;
                                tempRect.Y = Convert.ToInt32(xPosY.Value) + tempFrame.RenderRect.Y;
                                tempRect.Width = Convert.ToInt32(xWidth.Value);
                                tempRect.Height = Convert.ToInt32(xHeight.Value);

                                tempFrame.CollisionRect = tempRect;
                                tempAnim.FrameList.Add(tempFrame);
                            }
                        }
                    }
                    //AnimationSet.Add(tempAnim);
                    listBox_AnimationList.Items.Add(tempAnim);
                    string tempTexturePath = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Graphics\\Sprites\\");
                    nImageID = TM.LoadTexture(tempTexturePath + szTextureName);

                    //numericUpDown_AnchorX.Maximum = TM.GetTextureWidth(nImageID);
                    //numericUpDown_AnchorY.Maximum = TM.GetTextureHeight(nImageID);
                    //numericUpDown_RenderLeft.Maximum = TM.GetTextureWidth(nImageID);
                    //numericUpDown_RenderTop.Maximum = TM.GetTextureHeight(nImageID);
                    //numericUpDown_RenderRight.Maximum = TM.GetTextureWidth(nImageID);
                    //numericUpDown_RenderBottom.Maximum = TM.GetTextureHeight(nImageID);

                    //numericUpDown_CollisionLeft.Maximum = TM.GetTextureWidth(nImageID);
                    //numericUpDown_CollisionTop.Maximum = TM.GetTextureHeight(nImageID);
                    //numericUpDown_CollisionRight.Maximum = TM.GetTextureWidth(nImageID);
                    //numericUpDown_CollisionBottom.Maximum = TM.GetTextureHeight(nImageID);

                    //numericUpDown_AnchorX.Maximum = TM.GetTextureWidth(nImageID);
                    //numericUpDown_AnchorY.Maximum = TM.GetTextureHeight(nImageID);
                }
            }
        }

        private void listBox_FrameList_SelectedIndexChanged(object sender, EventArgs e)
        {
            //button_EditFrame.Enabled = true;

            if (listBox_FrameList.SelectedIndex > -1)
            {
                CFrame temp = (CFrame)listBox_FrameList.Items[listBox_FrameList.SelectedIndex];
                numericUpDown_RenderLeft.Value = temp.RenderRect.X;
                numericUpDown_RenderTop.Value = temp.RenderRect.Y;
                numericUpDown_RenderRight.Value = temp.RenderRect.Width;
                numericUpDown_RenderBottom.Value = temp.RenderRect.Height;

                numericUpDown_CollisionLeft.Value = temp.CollisionRect.X;
                numericUpDown_CollisionTop.Value = temp.CollisionRect.Y;
                numericUpDown_CollisionRight.Value = temp.CollisionRect.Width;
                numericUpDown_CollisionBottom.Value = temp.CollisionRect.Height;

                numericUpDown_AnchorX.Value = temp.Anchor.X;
                numericUpDown_AnchorY.Value = temp.Anchor.Y;
                numericUpDown_FrameDuration.Value = temp.Duration;
                textBox_EventString.Text = temp.EventID;
            }
        }

        private void listBox_AnimationList_SelectedIndexChanged(object sender, EventArgs e)
        {
            listBox_FrameList.Items.Clear();
            CAnimation temp = (CAnimation)listBox_AnimationList.Items[listBox_AnimationList.SelectedIndex];
            CFrame tFrame;
            for (int i = 0; i < temp.FrameList.Count; i++)
            {
                tFrame = temp.FrameList[i];
                listBox_FrameList.Items.Add(tFrame);
            }
            if (listBox_AnimationList.SelectedIndex > -1)
            {
                textBox_AnimationName.Text = temp.AnimationName;
                checkBox_AnimationLooping.Checked = temp.AnimationLooping;
                if (listBox_FrameList.SelectedIndex > -1)
                {
                    numericUpDown_RenderLeft.Value = temp.FrameList[listBox_FrameList.SelectedIndex].RenderRect.X;
                    numericUpDown_RenderTop.Value = temp.FrameList[listBox_FrameList.SelectedIndex].RenderRect.Y;
                    numericUpDown_RenderRight.Value = temp.FrameList[listBox_FrameList.SelectedIndex].RenderRect.Width;
                    numericUpDown_RenderBottom.Value = temp.FrameList[listBox_FrameList.SelectedIndex].RenderRect.Height;

                    numericUpDown_CollisionLeft.Value = temp.FrameList[listBox_FrameList.SelectedIndex].CollisionRect.X;
                    numericUpDown_CollisionTop.Value = temp.FrameList[listBox_FrameList.SelectedIndex].CollisionRect.Y;
                    numericUpDown_CollisionRight.Value = temp.FrameList[listBox_FrameList.SelectedIndex].CollisionRect.Width;
                    numericUpDown_CollisionBottom.Value = temp.FrameList[listBox_FrameList.SelectedIndex].CollisionRect.Height;

                    numericUpDown_AnchorX.Value = temp.FrameList[listBox_FrameList.SelectedIndex].Anchor.X;
                    numericUpDown_AnchorY.Value = temp.FrameList[listBox_FrameList.SelectedIndex].Anchor.Y;
                    numericUpDown_FrameDuration.Value = temp.FrameList[listBox_FrameList.SelectedIndex].Duration;
                    textBox_EventString.Text = temp.FrameList[listBox_FrameList.SelectedIndex].EventID;

                }
            }

        }

        private void button_RenderRectTool_Click(object sender, EventArgs e)
        {
            button_RenderRectTool.Enabled = false;
            button_CollisionRectTool.Enabled = true;
            button_AnchorPointTool.Enabled = true;
        }

        private void button_CollisionRectTool_Click(object sender, EventArgs e)
        {
            button_RenderRectTool.Enabled = true;
            button_CollisionRectTool.Enabled = false;
            button_AnchorPointTool.Enabled = true;
        }

        private void button_AnchorPointTool_Click(object sender, EventArgs e)
        {
            button_RenderRectTool.Enabled = true;
            button_CollisionRectTool.Enabled = true;
            button_AnchorPointTool.Enabled = false;
        }

        private void splitContainer1_Panel2_MouseClick(object sender, MouseEventArgs e)
        {
            button_EditFrame.Enabled = true;
            if (!bMouseDown)
            {
                bMouseDown = true;
                if (button_RenderRectTool.Enabled == false)
                {
                    Rectangle tempRect = new Rectangle();
                    tempRect.X = e.X;
                    tempRect.Y = e.Y;

                    workingFrame.RenderRect = tempRect;

                }
                else if (button_CollisionRectTool.Enabled == false)
                {
                    Rectangle tempRect = new Rectangle();
                    tempRect.X = e.X;
                    tempRect.Y = e.Y;

                    workingFrame.CollisionRect = tempRect;
                }
                else if (button_AnchorPointTool.Enabled == false)
                {
                    Point tempPoint = new Point();
                    tempPoint.X = e.X;
                    tempPoint.Y = e.Y;

                    workingFrame.Anchor = tempPoint;
                }

            }
            else
            {
                if (button_RenderRectTool.Enabled == false)
                {
                    bMouseDown = false;

                }
                else if (button_CollisionRectTool.Enabled == false)
                {
                    bMouseDown = false;
                }
                else if (button_AnchorPointTool.Enabled == false)
                {
                    bMouseDown = false;
                }

            }
        }

        private void splitContainer1_Panel2_MouseUp(object sender, MouseEventArgs e)
        {

        }

        private void splitContainer1_Panel2_MouseMove(object sender, MouseEventArgs e)
        {
            if (bMouseDown)
            {
                if (button_RenderRectTool.Enabled == false)
                {
                    Rectangle tempRect = workingFrame.RenderRect;
                    tempRect.Width = e.X - tempRect.X;
                    tempRect.Height = e.Y - tempRect.Y;

                    workingFrame.RenderRect = tempRect;

                }
                else if (button_CollisionRectTool.Enabled == false)
                {
                    Rectangle tempRect = workingFrame.CollisionRect;
                    tempRect.Width = e.X - tempRect.X;
                    tempRect.Height = e.Y - tempRect.Y;

                    workingFrame.CollisionRect = tempRect;
                }
            }
        }

        private void button_DeleteFrame_Click(object sender, EventArgs e)
        {
            if (listBox_FrameList.Items.Count > 0)
            {
                CAnimation temp = (CAnimation)listBox_AnimationList.Items[listBox_AnimationList.SelectedIndex];
                listBox_FrameList.Items.RemoveAt(listBox_AnimationList.SelectedIndex);
                temp.FrameList.RemoveAt(listBox_AnimationList.SelectedIndex);
            }
        }

        private void button_EditFrame_Click(object sender, EventArgs e)
        {
            if (listBox_FrameList.SelectedIndex != -1)
            {
                button_EditFrame.Enabled = false;
                button_DoneEdit.Enabled = true;
            }

        }

        private void numericUpDown_RenderLeft_ValueChanged(object sender, EventArgs e)
        {
            if (button_EditFrame.Enabled == false)
            {
                workingFrame = (CFrame)listBox_FrameList.Items[listBox_FrameList.SelectedIndex];
                Rectangle rTemp = workingFrame.RenderRect;
                Point pTemp = workingFrame.Anchor;
                Rectangle cTemp = workingFrame.RenderRect;

                rTemp.X = Convert.ToInt32(numericUpDown_RenderLeft.Value);
                rTemp.Y = Convert.ToInt32(numericUpDown_RenderTop.Value);
                rTemp.Width = Convert.ToInt32(numericUpDown_RenderRight.Value);
                rTemp.Height = Convert.ToInt32(numericUpDown_RenderBottom.Value);

                pTemp.X = Convert.ToInt32(numericUpDown_AnchorX.Value);
                pTemp.Y = Convert.ToInt32(numericUpDown_AnchorY.Value);

                cTemp.X = Convert.ToInt32(numericUpDown_CollisionLeft.Value);
                cTemp.Y = Convert.ToInt32(numericUpDown_CollisionTop.Value);
                cTemp.Width = Convert.ToInt32(numericUpDown_CollisionRight.Value);
                cTemp.Height = Convert.ToInt32(numericUpDown_CollisionBottom.Value);



                workingFrame.RenderRect = rTemp;
                workingFrame.CollisionRect = cTemp;
                workingFrame.Anchor = pTemp;
                workingFrame.Duration = Convert.ToDecimal(numericUpDown_FrameDuration.Value);
                workingFrame.EventID = textBox_EventString.Text;

                listBox_FrameList.Items[listBox_FrameList.SelectedIndex] = workingFrame;


            }
        }

        private void button_DoneEdit_Click(object sender, EventArgs e)
        {
            button_DoneEdit.Enabled = false;
            button_EditFrame.Enabled = true;
        }

        private void button_PreviousFrame_Click(object sender, EventArgs e)
        {
            if (listBox_FrameList.SelectedIndex > -1)
            {
                if (listBox_FrameList.SelectedIndex == 0)
                    listBox_FrameList.SelectedIndex = listBox_FrameList.Items.Count - 1;
                else
                    listBox_FrameList.SelectedIndex--;
            }
        }

        private void button_NextFrame_Click(object sender, EventArgs e)
        {
            if (listBox_FrameList.SelectedIndex > -1)
            {
                if (listBox_FrameList.SelectedIndex == listBox_FrameList.Items.Count - 1)
                    listBox_FrameList.SelectedIndex = 0;
                else
                    listBox_FrameList.SelectedIndex++;
            }
        }

        private void button_Reset_Click(object sender, EventArgs e)
        {
            if (listBox_FrameList.SelectedIndex > -1)
                listBox_FrameList.SelectedIndex = 0;
        }

        private void button_PlayStopAnimation_Click(object sender, EventArgs e)
        {
            if (bPlaying == false)
            {
                bPlaying = true;
            }
            else if (bPlaying == true)
            {
                bPlaying = false;
                sw.Reset();
            }
        }
    }
}