using System;
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

namespace SGP_PoA_LevelEditor
{
    public partial class Form1 : Form
    {


        string szFileName;
        string szRelativePath;
        string szTileSetName;
        bool looping = true;
        bool ShowGrid = true;
        bool mouseDown = false;
        bool rmouseDown = false;
        bool bSelectColor = false;
        Color cTransparency = Color.Magenta;

        Size MapSize = new Size(5, 5);
        Size TileSize = new Size(64, 64);
        Size TileSet = new Size(4, 4);
        Size MouseLoc = new Size(0, 0);
        Point tileSelected = new Point(0, 0);
        Point mapTile = new Point(0, 0);

        int imageID = -1;

        CSGP_Direct3D DX = CSGP_Direct3D.GetInstance();
        CSGP_TextureManager TM = CSGP_TextureManager.GetInstance();

        public bool isLooping
        {
            get { return looping; }
            set { looping = value; }
        }

        public Form1()
        {
            InitializeComponent();
        }

        public new void Update()
        {
            if (nudTileWidth.Value == 1 && nudTileHeight.Value == 1)
                nudTileHeight.Value = 8;


            if (imageID != -1)
            {
                if (TileSet.Width != Convert.ToInt32(nudTileWidth.Value))
                    TileSet.Width = TM.GetTextureWidth(imageID) / TileSize.Width;
                if (TileSet.Height != Convert.ToInt32(nudTileHeight.Value))
                    TileSet.Height = TM.GetTextureHeight(imageID) / TileSize.Height;
            }

            TileSize.Width = Convert.ToInt32(nudTileWidth.Value);
            TileSize.Height = Convert.ToInt32(nudTileHeight.Value);

            if (MapSize.Width != Convert.ToInt32(nudMapWidth.Value) || MapSize.Height != Convert.ToInt32(nudMapHeight.Value))
            {
                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    myLayers tLayer = new myLayers();
                    tLayer.MyTiles = new myTile[Convert.ToInt32(nudMapWidth.Value), Convert.ToInt32(nudMapHeight.Value)];
                    myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                    for (int x = 0; x < MapSize.Width; x++)
                    {
                            for (int y = 0; y < MapSize.Height; y++)
                            {
                                if (y < nudMapHeight.Value && x < nudMapWidth.Value)
                                    tLayer.MyTiles[x, y] = L.MyTiles[x, y];
                                else
                                {
                                    if (x < Convert.ToInt32(nudMapWidth.Value) && y < Convert.ToInt32(nudMapHeight.Value))
                                    {
                                        tLayer.MyTiles[x, y].X = -1;
                                        tLayer.MyTiles[x, y].Y = -1;
                                    }
                                }
                            }
                    }
                    lstLayers.Items[lstLayers.SelectedIndex] = tLayer;
                }
                MapSize.Width = Convert.ToInt32(nudMapWidth.Value);
                MapSize.Height = Convert.ToInt32(nudMapHeight.Value);
                panel2.AutoScrollMinSize = new Size(MapSize.Width * TileSize.Width, MapSize.Height * TileSize.Height);
            }
        }

        public void Render()
        {
            DX.Clear(panel2, Color.Magenta);
            DX.DeviceBegin();
            DX.SpriteBegin();

            if (imageID != -1)
            {
                for (int nLayer = lstLayers.SelectedIndex - 1; nLayer <= lstLayers.SelectedIndex; nLayer++)
                {
                    if (nLayer < 0)
                        continue;
                    myLayers L = (myLayers)lstLayers.Items[nLayer];
                    for (int y = 0; y < MapSize.Height; y++)
                    {
                        for (int x = 0; x < MapSize.Width; x++)
                        {
                            int nX = x * TileSize.Width;
                            int nY = y * TileSize.Height;
                            if (L.MyTiles[x, y].X != -1)
                            {
                                if (L.MyTiles[x, y].IsBlocked)
                                    TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                    new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                     TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(255, 255, 127, 127));
                                else if (L.MyTiles[x, y].IsWarp)
                                {
                                    TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                    new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                     TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(255, 0, 127, 255));
                                }
                                else
                                    TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                        new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                        TileSize.Width, TileSize.Height));
                            }
                        }
                    }
                }

                if (radMap.Checked)
                    TM.Draw(imageID, MouseLoc.Width * TileSize.Width + panel2.AutoScrollPosition.X, MouseLoc.Height * TileSize.Height + panel2.AutoScrollPosition.Y, 1, 1, new Rectangle(tileSelected.X * TileSize.Width + panel2.AutoScrollPosition.X, tileSelected.Y * TileSize.Height + panel2.AutoScrollPosition.Y, TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(127, 255, 255, 255));
            }
            if (ShowGrid)
            {
                for (int x = 0; x < MapSize.Width; x++)
                {
                    for (int y = 0; y < MapSize.Height; y++)
                    {
                        DX.DrawHollowRect(new Rectangle(x * TileSize.Width + panel2.AutoScrollPosition.X, y * TileSize.Height + panel2.AutoScrollPosition.Y, TileSize.Width, TileSize.Height), Color.White, 1);
                    }
                }
            }


            DX.SpriteEnd();
            DX.DeviceEnd();
            DX.Present();

            DX.Clear(panel1, Color.Black);
            DX.DeviceBegin();
            DX.SpriteBegin();
            if (imageID != -1)
                TM.Draw(imageID, panel1.AutoScrollPosition.X, panel1.AutoScrollPosition.Y, 1, 1, Rectangle.Empty, 0, 0, 0);

            if (ShowGrid)
            {
                for (int x = 0; x < TileSet.Width; x++)
                {
                    for (int y = 0; y < TileSet.Height; y++)
                    {
                        DX.DrawHollowRect(new Rectangle(x * TileSize.Width + panel1.AutoScrollPosition.X, y * TileSize.Height + panel1.AutoScrollPosition.Y, TileSize.Width, TileSize.Height), Color.White, 1);
                    }
                }
            }

            DX.DrawHollowRect(new Rectangle(tileSelected.X * TileSize.Width + panel1.AutoScrollPosition.X, tileSelected.Y * TileSize.Height + panel1.AutoScrollPosition.Y, TileSize.Width, TileSize.Height), Color.Red, 3);

            DX.SpriteEnd();
            DX.DeviceEnd();
            DX.Present();
        }

        public void Initialize()
        {

            cTransparency = Color.Black;
            szRelativePath = Environment.CurrentDirectory + "\\..\\Assets\\Graphics\\Tilesets\\";
            szTileSetName = "";
            szFileName = "";
            lstMaps.Items.Clear();
            lstLayers.Items.Clear();
            foreach (string szMapID in Directory.GetFiles(Environment.CurrentDirectory + "\\..\\Assets\\Data\\Levels\\", "*.xml").Select(Path.GetFileName))
            {
                lstMaps.Items.Add(szMapID);
            }

            DX.Initialize(panel2, false);
            DX.AddRenderTarget(panel1);

            if (imageID != -1)
                TM.UnloadTexture(imageID);

            imageID = -1;

            TM.Initialize(DX.Device, DX.Sprite);

            myLayers tempLayer = new myLayers();
            tempLayer.MyTiles = new myTile[MapSize.Width, MapSize.Height];

            for (int y = 0; y < MapSize.Height; y++)
            {
                for (int x = 0; x < MapSize.Width; x++)
                {
                    tempLayer.MyTiles[x, y].X = -1;
                    tempLayer.MyTiles[x, y].Y = -1;
                }
            }
            lstLayers.Items.Add(tempLayer);
            lstLayers.SelectedIndex = 0;

            TileSize.Height = 32;
            TileSize.Width = 32;

            nudTileHeight.Value = TileSize.Height;
            nudTileWidth.Value = TileSize.Width;

            MapSize = new Size(5, 5);

            nudMapHeight.Value = MapSize.Height;
            nudMapWidth.Value = MapSize.Width;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            isLooping = false;
        }

        private void exitToolStripMenuItfem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            int nTempX = (e.Location.X - panel1.AutoScrollPosition.X) / TileSize.Width;
            int nTempY = (e.Location.Y - panel1.AutoScrollPosition.Y) / TileSize.Height;
            tileSelected = new Point(nTempX, nTempY);
        }



        private void panel2_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.X - panel2.AutoScrollPosition.X < MapSize.Width * TileSize.Width &&
                e.Y - panel2.AutoScrollPosition.Y < MapSize.Height * TileSize.Height && e.X - panel2.AutoScrollPosition.X > 0 && e.Y - panel2.AutoScrollPosition.Y > 0)
            {
                Point Temp = new Point((e.X - panel2.AutoScrollPosition.X) / TileSize.Width, (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);
                myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];

                if (radMap.Checked)
                {
                    if (e.Button == MouseButtons.Right)
                    {
                        L.MyTiles[Temp.X, Temp.Y].X = -1;
                        L.MyTiles[Temp.X, Temp.Y].Y = -1;
                    }
                    else
                    {
                        L.MyTiles[Temp.X, Temp.Y].X = tileSelected.X;
                        L.MyTiles[Temp.X, Temp.Y].Y = tileSelected.Y;
                    }
                }

                if (radBlock.Checked)
                {
                    if (e.Button == MouseButtons.Left)
                    {
                        L.MyTiles[Temp.X, Temp.Y].IsBlocked = true;
                    }
                    else
                    {
                        L.MyTiles[Temp.X, Temp.Y].IsBlocked = false;
                    }

                }

                if (radWarp.Checked)
                {
                    if (e.Button == MouseButtons.Left)
                    {
                        if (L.MyTiles[Temp.X, Temp.Y].IsWarp == false)
                        {
                            mapTile = Temp;
                            if (L.MyTiles[Temp.X, Temp.Y].IsBlocked)
                                L.MyTiles[Temp.X, Temp.Y].IsBlocked = false;
                            else if (L.MyTiles[Temp.X, Temp.Y].IsNPC)
                                L.MyTiles[Temp.X, Temp.Y].IsNPC = false;

                            L.MyTiles[Temp.X, Temp.Y].IsWarp = true;
                            if (lstMaps.SelectedIndex >= 0 && lstMaps.Items.Count > 0)
                                L.MyTiles[Temp.X, Temp.Y].SzSpecial = lstMaps.Items[lstMaps.SelectedIndex].ToString();
                            else
                                L.MyTiles[Temp.X, Temp.Y].SzSpecial = "";
                            L.MyTiles[Temp.X, Temp.Y].WarpX = Convert.ToInt32(nudWarpX.Value);
                            L.MyTiles[Temp.X, Temp.Y].WarpY = Convert.ToInt32(nudWarpY.Value);
                        }
                        else
                        {
                            mapTile = Temp;
                            nudWarpX.Value = L.MyTiles[Temp.X, Temp.Y].WarpX;
                            nudWarpY.Value = L.MyTiles[Temp.X, Temp.Y].WarpY;
                            for (int i = 0; i < lstMaps.Items.Count; i++)
                            {
                                if (lstMaps.Items[i].ToString() == L.MyTiles[mapTile.X, mapTile.Y].SzSpecial)
                                {
                                    lstMaps.SelectedIndex = i;
                                    break;
                                }
                            }

                            btnWarp.Enabled = false;
                            btnWarpCancel.Enabled = false;
                        }
                    }
                    else
                    {
                        L.MyTiles[Temp.X, Temp.Y].IsWarp = false;
                        L.MyTiles[Temp.X, Temp.Y].SzSpecial = "";
                        L.MyTiles[Temp.X, Temp.Y].WarpX = 0;
                        L.MyTiles[Temp.X, Temp.Y].WarpY = 0;
                    }
                }

                if (radNPC.Checked)
                {
                    if (grpWayPoints.Visible)
                    {
                        if (e.Button == MouseButtons.Left)
                        {
                            if (radWPAdd.Checked)
                            {


                            }
                            else if (radWPMove.Checked)
                            {


                            }
                        }
                        else
                        {
                            //Delete
                        }
                    }
                    else
                    {
                        if (e.Button == MouseButtons.Left)
                        {
                            if (L.MyTiles[Temp.X, Temp.Y].IsNPC == false)
                            {
                                mapTile = Temp;
                                if (L.MyTiles[Temp.X, Temp.Y].IsBlocked)
                                    L.MyTiles[Temp.X, Temp.Y].IsBlocked = false;
                                else if (L.MyTiles[Temp.X, Temp.Y].IsWarp)
                                    L.MyTiles[Temp.X, Temp.Y].IsWarp = false;
                            }
                            else
                            {

                            }
                        }
                        else
                        {
                            //Delete
                        }

                    }
                }
                lstLayers.Items[lstLayers.SelectedIndex] = L;
            }
        }

        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.X - panel2.AutoScrollPosition.X < MapSize.Width * TileSize.Width &&
                e.Y - panel2.AutoScrollPosition.Y < MapSize.Height * TileSize.Height && e.X - panel2.AutoScrollPosition.X > 0 && e.Y - panel2.AutoScrollPosition.Y > 0)
            {
                MouseLoc.Width = (e.X - panel2.AutoScrollPosition.X) / TileSize.Width;
                MouseLoc.Height = (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height;
                myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                Point Temp = new Point((e.X - panel2.AutoScrollPosition.X) / TileSize.Width, (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);

                if (radMap.Checked)
                {
                    if (mouseDown)
                    {
                        L.MyTiles[Temp.X, Temp.Y].X = tileSelected.X;
                        L.MyTiles[Temp.X, Temp.Y].Y = tileSelected.Y;
                    }
                    else if (rmouseDown)
                    {
                        L.MyTiles[Temp.X, Temp.Y].X = -1;
                        L.MyTiles[Temp.X, Temp.Y].Y = -1;
                    }
                }
                else if (radBlock.Checked)
                {
                    if (mouseDown)
                    {
                        L.MyTiles[Temp.X, Temp.Y].IsBlocked = true;
                    }
                    else if (rmouseDown)
                    {
                        L.MyTiles[Temp.X, Temp.Y].IsBlocked = false;
                    }

                }
                lstLayers.Items[lstLayers.SelectedIndex] = L;
            }
        }

        private void button1_MouseClick(object sender, MouseEventArgs e)
        {
            ShowGrid = !ShowGrid;
        }

        private void panel2_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                mouseDown = false;
            else if (e.Button == MouseButtons.Right)
                rmouseDown = false;

        }

        private void panel2_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                mouseDown = true;
            else if (e.Button == MouseButtons.Right)
                rmouseDown = true;
        }

        private void panel1_Scroll(object sender, ScrollEventArgs e)
        {
            Render();
        }

        private void saveMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (szFileName == "" || File.Exists(szFileName) == false)
                saveAsToolStripMenuItem_Click(sender, e);
            else
            {
                XElement xRoot = new XElement("World");
                XAttribute xWidth = new XAttribute("Width", MapSize.Width);
                XAttribute xHeight = new XAttribute("Height", MapSize.Height);
                XAttribute xTotalLayers = new XAttribute("Layers", lstLayers.Items.Count);
                XAttribute xTileWidth = new XAttribute("TileWidth", TileSize.Width);
                XAttribute xTileHeight = new XAttribute("TileHeight", TileSize.Height);
                XAttribute xImageLocation = new XAttribute("Image", szTileSetName);
                XAttribute xColorTrans = new XAttribute("Transparency", cTransparency.ToArgb());

                xRoot.Add(xWidth);
                xRoot.Add(xHeight);
                xRoot.Add(xTotalLayers);
                xRoot.Add(xTileWidth);
                xRoot.Add(xTileHeight);
                xRoot.Add(xImageLocation);
                xRoot.Add(xColorTrans);

                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    XElement xLayer = new XElement("Layer");
                    XAttribute xID = new XAttribute("ID", nLayer);
                    xLayer.Add(xID);
                    xRoot.Add(xLayer);
                    myLayers L = (myLayers)lstLayers.Items[nLayer];

                    for (int y = 0; y < MapSize.Height; y++)
                    {

                        for (int x = 0; x < MapSize.Width; x++)
                        {
                            XElement xTile = new XElement("Tile");
                            XAttribute xTileID = new XAttribute("ID", y * MapSize.Width + x);
                            xTile.Add(xTileID);
                            xLayer.Add(xTile);
                            XAttribute xPosX = new XAttribute("posX", x);
                            XAttribute xPosY = new XAttribute("posY", y);
                            xTile.Add(xPosX);
                            xTile.Add(xPosY);
                            XElement xTileData = new XElement("Tile_Data");
                            XAttribute xTileX = new XAttribute("xTileID", L.MyTiles[x, y].X);
                            XAttribute xTileY = new XAttribute("yTileID", L.MyTiles[x, y].Y);
                            XAttribute xTileBlock = new XAttribute("isBlocked", L.MyTiles[x, y].IsBlocked);
                            XAttribute xTileNpc = new XAttribute("isNPC", L.MyTiles[x, y].IsNPC);
                            XAttribute xTileEvent = new XAttribute("isEvent", L.MyTiles[x, y].IsEvent);
                            XAttribute xTileWarp = new XAttribute("isWARP", L.MyTiles[x, y].IsWarp);
                            XAttribute xTileWarpX = new XAttribute("WarpX", L.MyTiles[x, y].WarpX);
                            XAttribute xTileWarpY = new XAttribute("WarpY", L.MyTiles[x, y].WarpY);
                            if (L.MyTiles[x, y].SzSpecial == null)
                                L.MyTiles[x, y].SzSpecial = "";
                            XAttribute xEventId = new XAttribute("EventID", L.MyTiles[x, y].SzSpecial);

                            xTileData.Add(xTileX);
                            xTileData.Add(xTileY);
                            xTileData.Add(xTileBlock);
                            xTileData.Add(xTileNpc);
                            xTileData.Add(xTileEvent);
                            xTileData.Add(xEventId);
                            xTileData.Add(xTileWarp);
                            xTileData.Add(xTileWarpX);
                            xTileData.Add(xTileWarpY);

                            xTile.Add(xTileData);
                        }
                    }
                }
                xRoot.Save(szFileName);

            }

        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            string temp = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Data\\Levels");
            dlg.InitialDirectory = temp;
            dlg.Filter = "All Files|*.*|XML Files|*.xml";
            dlg.FilterIndex = 2;
            dlg.DefaultExt = "xml";

            if (DialogResult.OK == dlg.ShowDialog())
            {
                XElement xRoot = new XElement("World");
                XAttribute xWidth = new XAttribute("Width", MapSize.Width);
                XAttribute xHeight = new XAttribute("Height", MapSize.Height);
                XAttribute xTotalLayers = new XAttribute("Layers", lstLayers.Items.Count);
                XAttribute xTileWidth = new XAttribute("TileWidth", TileSize.Width);
                XAttribute xTileHeight = new XAttribute("TileHeight", TileSize.Height);
                XAttribute xImageLocation = new XAttribute("Image", szTileSetName);
                XAttribute xColorTrans = new XAttribute("Transparency", cTransparency.ToArgb());

                xRoot.Add(xWidth);
                xRoot.Add(xHeight);
                xRoot.Add(xTotalLayers);
                xRoot.Add(xTileWidth);
                xRoot.Add(xTileHeight);
                xRoot.Add(xImageLocation);
                xRoot.Add(xColorTrans);

                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    XElement xLayer = new XElement("Layer");
                    XAttribute xID = new XAttribute("ID", nLayer);
                    xLayer.Add(xID);
                    xRoot.Add(xLayer);
                    myLayers L = (myLayers)lstLayers.Items[nLayer];

                    for (int y = 0; y < MapSize.Height; y++)
                    {
                        for (int x = 0; x < MapSize.Width; x++)
                        {
                            XElement xTile = new XElement("Tile");
                            XAttribute xTileID = new XAttribute("ID", y * MapSize.Width + x);
                            xTile.Add(xTileID);
                            xLayer.Add(xTile);
                            XAttribute xPosX = new XAttribute("posX", x);
                            XAttribute xPosY = new XAttribute("posY", y);
                            xTile.Add(xPosX);
                            xTile.Add(xPosY);
                            XElement xTileData = new XElement("Tile_Data");
                            XAttribute xTileX = new XAttribute("xTileID", L.MyTiles[x, y].X);
                            XAttribute xTileY = new XAttribute("yTileID", L.MyTiles[x, y].Y);
                            XAttribute xTileBlock = new XAttribute("isBlocked", L.MyTiles[x, y].IsBlocked);
                            XAttribute xTileNpc = new XAttribute("isNPC", L.MyTiles[x, y].IsNPC);
                            XAttribute xTileEvent = new XAttribute("isEvent", L.MyTiles[x, y].IsEvent);
                            XAttribute xTileWarp = new XAttribute("isWARP", L.MyTiles[x, y].IsWarp);
                            XAttribute xTileWarpX = new XAttribute("WarpX", L.MyTiles[x, y].WarpX);
                            XAttribute xTileWarpY = new XAttribute("WarpY", L.MyTiles[x, y].WarpY);
                            if (L.MyTiles[x, y].SzSpecial == null)
                                L.MyTiles[x, y].SzSpecial = "";
                            XAttribute xEventId = new XAttribute("EventID", L.MyTiles[x, y].SzSpecial);

                            xTileData.Add(xTileX);
                            xTileData.Add(xTileY);
                            xTileData.Add(xTileBlock);
                            xTileData.Add(xTileNpc);
                            xTileData.Add(xTileEvent);
                            xTileData.Add(xEventId);
                            xTileData.Add(xTileWarp);
                            xTileData.Add(xTileWarpX);
                            xTileData.Add(xTileWarpY);

                            xTile.Add(xTileData);
                        }
                    }
                }
                szFileName = dlg.FileName;
                xRoot.Save(dlg.FileName);
            }

        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            Point temp = new Point(e.Location.X, e.Location.Y);
        }

        private void newMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Initialize();
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string temp = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Data\\Levels");
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = temp;
            dlg.Filter = "All Files|*.*|XML Files|*.xml";
            dlg.FilterIndex = 2;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                Initialize();
                XElement xRoot = XElement.Load(dlg.FileName);
                IEnumerable<XElement> xLayers = xRoot.Elements();

                XAttribute xWidth = xRoot.Attribute("Width");
                XAttribute xHeight = xRoot.Attribute("Height");
                XAttribute xTotalLayers = xRoot.Attribute("Layers");
                XAttribute xTileWidth = xRoot.Attribute("TileWidth");
                XAttribute xTileHeight = xRoot.Attribute("TileHeight");
                XAttribute xTileImage = xRoot.Attribute("Image");
                XAttribute xColorTrans = xRoot.Attribute("Transparency");

                cTransparency = Color.FromArgb(Convert.ToInt32(xColorTrans.Value));

                if (xTileImage.Value.ToString() != "")
                {
                    szTileSetName = xTileImage.Value.ToString();
                    imageID = TM.LoadTexture(szRelativePath + szTileSetName, cTransparency);
                    panel1.AutoScrollMinSize = new Size(TM.GetTextureWidth(imageID), TM.GetTextureHeight(imageID));
                }
                else
                {
                    imageID = -1;
                    panel1.AutoScrollMinSize = new Size(panel1.ClientSize.Width, panel1.ClientSize.Height);
                }

                MapSize = new Size(Convert.ToInt32(xWidth.Value), Convert.ToInt32(xHeight.Value));
                TileSize = new Size(Convert.ToInt32(xTileWidth.Value), Convert.ToInt32(xTileHeight.Value));
                lstLayers.Items.Clear();
                myLayers lTemp = new myLayers();
                lTemp.MyTiles = new myTile[MapSize.Width, MapSize.Height];

                nudMapHeight.Value = MapSize.Height;
                nudMapWidth.Value = MapSize.Width;
                nudTileHeight.Value = TileSize.Height;
                nudTileWidth.Value = TileSize.Width;

                foreach (XElement Layers in xLayers)
                {
                    IEnumerable<XElement> xTiles = Layers.Elements();

                    foreach (XElement xTile in xTiles)
                    {
                        XAttribute xPosX = xTile.Attribute("posX");
                        XAttribute xPosY = xTile.Attribute("posY");

                        int nPosX = Convert.ToInt32(xPosX.Value);
                        int nPosY = Convert.ToInt32(xPosY.Value);

                        XElement xTileInfo = xTile.Element("Tile_Data");
                        XAttribute xTileX = xTileInfo.Attribute("xTileID");
                        XAttribute xTileY = xTileInfo.Attribute("yTileID");
                        XAttribute xTileBlock = xTileInfo.Attribute("isBlocked");
                        XAttribute xTileNpc = xTileInfo.Attribute("isNPC");
                        XAttribute xTileEvent = xTileInfo.Attribute("isEvent");
                        XAttribute xTileEventID = xTileInfo.Attribute("EventID");
                        XAttribute xTileWarp = xTileInfo.Attribute("isWARP");
                        XAttribute xTileWarpX = xTileInfo.Attribute("WarpX");
                        XAttribute xTileWarpY = xTileInfo.Attribute("WarpY");

                        myTile pTile = new myTile();
                        pTile.X = Convert.ToInt32(xTileX.Value);
                        pTile.Y = Convert.ToInt32(xTileY.Value);
                        pTile.IsBlocked = Convert.ToBoolean(xTileBlock.Value);
                        pTile.IsEvent = Convert.ToBoolean(xTileEvent.Value);
                        pTile.IsNPC = Convert.ToBoolean(xTileNpc.Value);
                        pTile.IsWarp = Convert.ToBoolean(xTileWarp.Value);
                        pTile.WarpX = Convert.ToInt32(xTileWarpX.Value);
                        pTile.WarpY = Convert.ToInt32(xTileWarpY.Value);
                        pTile.SzSpecial = xTileEventID.Value;
                        lTemp.MyTiles[nPosX, nPosY] = pTile;
                    }
                    lstLayers.Items.Add(lTemp);
                    lTemp.MyTiles = new myTile[MapSize.Width, MapSize.Height];
                }
                szFileName = dlg.FileName;
            }
            lstLayers.SelectedIndex = lstLayers.Items.Count - 1;
            panel2.AutoScrollMinSize = new Size(MapSize.Width * TileSize.Width, MapSize.Height * TileSize.Height);
            if (lstLayers.Items.Count > 1)
                btnDelete.Enabled = true;
        }

        private void panel1_Resize(object sender, EventArgs e)
        {
            DX.Resize(panel1, panel1.ClientSize.Width, panel1.ClientSize.Height, false);
        }

        private void panel2_Resize(object sender, EventArgs e)
        {
            DX.Resize(panel2, panel2.ClientSize.Width, panel2.ClientSize.Height, false);
        }

        private void panel2_Scroll(object sender, ScrollEventArgs e)
        {
            Render();
        }

        private void loadTilesetToolStripMenuItem_Click(object sender, EventArgs e)
        {

            OpenFileDialog dlg = new OpenFileDialog();
            string temp = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Graphics\\Tilesets");
            dlg.InitialDirectory = temp;
            dlg.Filter = "All Files|*.*";
            dlg.FilterIndex = 2;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                if (imageID != -1)
                    TM.UnloadTexture(imageID);
                szTileSetName = Path.GetFileName(dlg.FileName);
                if (!File.Exists(szRelativePath + szTileSetName))
                    File.Copy(dlg.FileName, szRelativePath + szTileSetName);

                imageID = TM.LoadTexture(szRelativePath + szTileSetName, cTransparency);
                panel1.AutoScrollMinSize = new Size(TM.GetTextureWidth(imageID), TM.GetTextureHeight(imageID));
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            if (bSelectColor)
            {
                if (e.X > 0 && e.X < panel1.Width && e.Y > 0 && e.Y < panel1.Height)
                {
                    if (imageID != -1)
                    {
                        Bitmap b = new Bitmap(szRelativePath + szTileSetName);
                        cTransparency = b.GetPixel(e.X - panel1.AutoScrollPosition.X, e.Y - panel1.AutoScrollPosition.Y);
                        TM.UnloadTexture(imageID);
                        imageID = TM.LoadTexture(szRelativePath + szTileSetName, cTransparency);
                    }
                    bSelectColor = false;
                    label6.Text = "";
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            bSelectColor = true;
            label6.Text = "Choose a Color";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
            for (int x = 0; x < MapSize.Width; x++)
            {
                for (int y = 0; y < MapSize.Height; y++)
                {
                    L.MyTiles[x, y].X = tileSelected.X;
                    L.MyTiles[x, y].Y = tileSelected.Y;
                }
            }
            lstLayers.Items[lstLayers.SelectedIndex] = L;
        }

        private void radWarp_CheckedChanged(object sender, EventArgs e)
        {
            grpWarp.Visible = radWarp.Checked;
            if (radWarp.Checked == false)
            {
                btnWarp.Enabled = false;
                btnWarpCancel.Enabled = false;
            }
        }

        private void txtWarp_TextChanged(object sender, EventArgs e)
        {
            if (btnWarp.Enabled == false)
            {
                btnWarp.Enabled = true;
                btnWarpCancel.Enabled = true;
            }
        }

        private void btnWarp_Click(object sender, EventArgs e)
        {
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
            if (lstMaps.SelectedIndex >= 0 && lstMaps.Items.Count > 0)
                L.MyTiles[mapTile.X, mapTile.Y].SzSpecial = lstMaps.Items[lstMaps.SelectedIndex].ToString();
            else
                L.MyTiles[mapTile.X, mapTile.Y].SzSpecial = "";
            L.MyTiles[mapTile.X, mapTile.Y].WarpX = Convert.ToInt32(nudWarpX.Value);
            L.MyTiles[mapTile.X, mapTile.Y].WarpY = Convert.ToInt32(nudWarpY.Value);

            lstLayers.Items[lstLayers.SelectedIndex] = L;
            btnWarp.Enabled = false;
            btnWarpCancel.Enabled = false;
        }

        private void btnWarpCancel_Click(object sender, EventArgs e)
        {
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];

            nudWarpX.Value = L.MyTiles[mapTile.X, mapTile.Y].WarpX;
            nudWarpY.Value = L.MyTiles[mapTile.X, mapTile.Y].WarpY;
            for (int i = 0; i < lstMaps.Items.Count; i++)
            {
                if (lstMaps.Items[i].ToString() == L.MyTiles[mapTile.X, mapTile.Y].SzSpecial)
                {
                    lstMaps.SelectedIndex = i;
                    break;
                }
            }

            btnWarp.Enabled = false;
            btnWarpCancel.Enabled = false;
        }

        private void radNPC_CheckedChanged(object sender, EventArgs e)
        {
            grpNPC.Visible = radNPC.Checked;
        }

        private void chkMoves_CheckedChanged(object sender, EventArgs e)
        {
            btnNPCMove.Enabled = chkMoves.Checked;
            if (grpWayPoints.Visible && !chkMoves.Checked)
                grpWayPoints.Visible = false;
        }

        private void chkHostile_CheckedChanged(object sender, EventArgs e)
        {
            btnNPCUnits.Enabled = chkHostile.Checked;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            btnNpcAdd.Enabled = true;
            btnNpcApply.Enabled = true;
            btnNpcCancel.Enabled = true;
        }

        private void btnNpcAdd_Click(object sender, EventArgs e)
        {

            btnNpcAdd.Enabled = false;
            btnNpcApply.Enabled = false;
            btnNpcCancel.Enabled = false;
        }

        private void btnNpcCancel_Click(object sender, EventArgs e)
        {
            btnNpcAdd.Enabled = false;
            btnNpcApply.Enabled = false;
            btnNpcCancel.Enabled = false;
        }

        private void btnNpcApply_Click(object sender, EventArgs e)
        {

            btnNpcAdd.Enabled = false;
            btnNpcApply.Enabled = false;
            btnNpcCancel.Enabled = false;
        }

        private void btnNPCMove_Click(object sender, EventArgs e)
        {
            grpWayPoints.Visible = !grpWayPoints.Visible;
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (lstLayers.Items.Count > 1)
            {
                int nTemp = lstLayers.SelectedIndex - 1;
                if (nTemp < 0)
                    nTemp = 0;
                lstLayers.Items.Remove(lstLayers.Items[lstLayers.SelectedIndex]);
                lstLayers.SelectedIndex = nTemp;
                if (lstLayers.Items.Count < 2)
                    btnDelete.Enabled = false;
            }
        }

        private void btnNewLayer_Click(object sender, EventArgs e)
        {
            myLayers lTemp = new myLayers();
            lTemp.MyTiles = new myTile[MapSize.Width, MapSize.Height];
            for (int y = 0; y < MapSize.Height; y++)
            {
                for (int x = 0; x < MapSize.Width; x++)
                {
                    lTemp.MyTiles[x, y].X = -1;
                    lTemp.MyTiles[x, y].Y = -1;
                }
            }
            lstLayers.Items.Add(lTemp);
            lstLayers.SelectedIndex = lstLayers.Items.Count - 1;
            btnDelete.Enabled = true;
        }

        private void btnShiftDown_Click(object sender, EventArgs e)
        {

        }

        private void lstLayers_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstLayers.SelectedIndex > 0)
                btnShiftUp.Enabled = true;
            else
                btnShiftUp.Enabled = false;

            if (lstLayers.SelectedIndex < lstLayers.Items.Count - 1)
                btnShiftDown.Enabled = true;
            else
                btnShiftDown.Enabled = false;
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];

            for (int y = 0; y < MapSize.Height; y++)
            {
                for (int x = 0; x < MapSize.Width; x++)
                {
                    L.MyTiles[x, y].X = -1;
                    L.MyTiles[x, y].Y = -1;
                }
            }
            lstLayers.Items[lstLayers.SelectedIndex] = L;
        }

    }

}
