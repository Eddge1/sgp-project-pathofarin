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
        bool bCreateRect = false;
        bool bChangedLayers = false;
        bool bFill = false;
        Rectangle rTemp;
        Rectangle rFill;
        Color cTransparency = Color.Magenta;

        Size TileSize = new Size(64, 64);
        Size TileSet = new Size(4, 4);
        Size MouseLoc = new Size(0, 0);
        Point tileSelected = new Point(0, 0);
        Point mapTile = new Point(0, 0);
        myNPC selectedNPC = new myNPC();

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

        }

        public void Render()
        {
            DX.Clear(panel2, Color.Magenta);
            DX.DeviceBegin();
            DX.SpriteBegin();

            if (imageID != -1)
            {
                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    if (nLayer < 0)
                        continue;
                    myLayers L = (myLayers)lstLayers.Items[nLayer];
                    for (int y = 0; y < L.LayerSize.Height; y++)
                    {
                        for (int x = 0; x < L.LayerSize.Width; x++)
                        {
                            int nX = x * TileSize.Width + L.OffSet.Width;
                            int nY = y * TileSize.Height + L.OffSet.Height;
                            if (nX > (panel2.AutoScrollPosition.X * -1) - TileSize.Width && nX < (panel2.AutoScrollPosition.X * -1) + panel2.ClientSize.Width + TileSize.Width)
                            {
                                if (nY > (panel2.AutoScrollPosition.Y * -1) - TileSize.Height && nY < (panel2.AutoScrollPosition.Y * -1) + panel2.ClientSize.Height + TileSize.Height)
                                {

                                    if (L.MyTiles[x, y].X != -1)
                                    {
                                        if (L.MyTiles[x, y].EventType == "WARP")
                                        {
                                            TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                            new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                             TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(255, 0, 127, 255));
                                        }
                                        else if (L.MyTiles[x, y].EventType == "EVENT")
                                        {
                                            TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                            new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                             TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(255, 25, 25, 25));
                                        }
                                        else if (L.MyTiles[x, y].EventType == "NPCS")
                                        {
                                            TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                            new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                             TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(255, 0, 255, 0));
                                        }
                                        else if (L.MyTiles[x, y].EventType == "CHESTS")
                                        {
                                            TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                            new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                             TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(255, 127, 0, 127));
                                        }
                                        else
                                            TM.Draw(imageID, nX + panel2.AutoScrollPosition.X, nY + panel2.AutoScrollPosition.Y, 1, 1,
                                                new Rectangle(L.MyTiles[x, y].X * TileSize.Width, L.MyTiles[x, y].Y * TileSize.Height,
                                                TileSize.Width, TileSize.Height));
                                    }
                                }
                            }
                        }
                    }
                }
                if (cmbMode.SelectedIndex >= 0)
                {
                    if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "MAP_EDIT")
                    {
                        myLayers Ls = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                        TM.Draw(imageID, MouseLoc.Width * TileSize.Width + panel2.AutoScrollPosition.X + Ls.OffSet.Width, MouseLoc.Height * TileSize.Height + panel2.AutoScrollPosition.Y + Ls.OffSet.Height, 1, 1, new Rectangle(tileSelected.X * TileSize.Width, tileSelected.Y * TileSize.Height, TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(127, 255, 255, 255));
                    }
                }
            }
            if (cmbMode.SelectedIndex >= 0)
            {
                if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "BLOCK")
                {
                    Rectangle r;
                    for (int i = 0; i < lstBlock.Items.Count; i++)
                    {
                        r = (Rectangle)lstBlock.Items[i];
                        r.X += panel2.AutoScrollPosition.X;
                        r.Y += panel2.AutoScrollPosition.Y;
                        DX.DrawRect(r, Color.FromArgb(127, 255, 0, 0));
                        if (bCreateRect)
                        {
                            r = rTemp;
                            r.X += panel2.AutoScrollPosition.X;
                            r.Y += panel2.AutoScrollPosition.Y;
                            DX.DrawHollowRect(r, Color.FromArgb(255, 0, 0, 0), 1);
                        }
                    }
                }
            }

            if (lstWaypoints.Items.Count > 0)
            {
                for (int i = 0; i < lstWaypoints.Items.Count; i++)
                {
                    if (i != 0)
                    {
                        Point nPrev = (Point)lstWaypoints.Items[i - 1];
                        Point nNow = (Point)lstWaypoints.Items[i];
                        DX.DrawLine(nPrev.X + panel2.AutoScrollPosition.X, nPrev.Y + panel2.AutoScrollPosition.Y, nNow.X + panel2.AutoScrollPosition.X, nNow.Y + panel2.AutoScrollPosition.Y, Color.FromArgb(0, 255, 255), 2);
                    }
                }
                if (lstWaypoints.SelectedIndex >= 0)
                {
                    Point nNow = (Point)lstWaypoints.Items[lstWaypoints.SelectedIndex];
                    DX.DrawHollowRect(new Rectangle(nNow.X - 3 + panel2.AutoScrollPosition.X, nNow.Y - 3 + panel2.AutoScrollPosition.Y, 6, 6), Color.FromArgb(255, 0, 0), 3);
                }
            }



            if (ShowGrid)
            {
                myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                for (int x = 0; x < L.LayerSize.Width; x++)
                {
                    for (int y = 0; y < L.LayerSize.Height; y++)
                    {
                        DX.DrawHollowRect(new Rectangle(x * TileSize.Width + panel2.AutoScrollPosition.X + L.OffSet.Width, y * TileSize.Height + panel2.AutoScrollPosition.Y + L.OffSet.Height, TileSize.Width, TileSize.Height), Color.White, 1);
                    }
                }
            }

            if (bFill)
            {
                Rectangle rTemp = new Rectangle(rFill.X * TileSize.Width, rFill.Y * TileSize.Height, (rFill.Width - rFill.X) * TileSize.Width, (rFill.Height - rFill.Y) * TileSize.Height);
                DX.DrawHollowRect(rTemp, Color.Blue, 3);
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
            rFill = new Rectangle(-1, -1, -1, -1);
            cTransparency = Color.Black;

            selectedNPC = new myNPC();
            selectedNPC.Units = new List<myUnits>();

            szRelativePath = Environment.CurrentDirectory + "\\..\\Assets\\Graphics\\Tilesets\\";
            szTileSetName = "";
            szFileName = "";
            txtBroadCast.Text = "";
            txtChestBroadcast.Text = "";
            txtErase.Text = "";
            lstNPC.Items.Clear();
            lstMaps.Items.Clear();
            lstLayers.Items.Clear();
            lstBlock.Items.Clear();
            lblAudio.Text = "Click to set Audio ----->";

            foreach (string szMapID in Directory.GetFiles(Environment.CurrentDirectory + "\\..\\Assets\\Data\\Levels\\", "*.xml").Select(Path.GetFileName))
            {
                string szTemp = szMapID.Remove(szMapID.Length - 4, 4);
                lstMaps.Items.Add(szTemp);
            }
            foreach (string szMapID in Directory.GetFiles(Environment.CurrentDirectory + "\\..\\Assets\\Data\\NPCS\\", "*.xml").Select(Path.GetFileName))
            {
                string szTemp = szMapID.Remove(szMapID.Length - 4, 4);
                lstNPC.Items.Add(szTemp);
            }
            cmbMode.Items.Clear();
            cmbMode.Items.Add("MAP_EDIT");
            cmbMode.Items.Add("BLOCK");
            cmbMode.Items.Add("EVENT");
            cmbMode.Items.Add("NPCS");
            cmbMode.Items.Add("WARP");
            cmbMode.Items.Add("CHESTS");
            cmbAI.Items.Clear();
            cmbAI.Items.Add("BASIC");
            cmbItemChoice.Items.Clear();
            cmbItemChoice.Items.Add("Potion");
            cmbItemChoice.Items.Add("Hi-Potion");
            cmbItemChoice.Items.Add("Titan-Potion");
            cmbItemChoice.Items.Add("Ether");
            cmbItemChoice.Items.Add("Hi-Ether");
            cmbItemChoice.Items.Add("Titan-Ether");

            cmbMode.SelectedIndex = 0;
            cmbItemChoice.SelectedIndex = 0;

            DX.Initialize(panel2, false);
            DX.AddRenderTarget(panel1);

            if (imageID != -1)
                TM.UnloadTexture(imageID);

            imageID = -1;

            TM.Initialize(DX.Device, DX.Sprite);

            myLayers tempLayer = new myLayers();
            tempLayer.MyTiles = new myTile[5, 5];
            tempLayer.LayerSize = new Size(5, 5);
            tempLayer.OffSet = new Size(0, 0);

            for (int y = 0; y < 5; y++)
            {
                for (int x = 0; x < 5; x++)
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

            nudMapHeight.Value = tempLayer.LayerSize.Height;
            nudMapWidth.Value = tempLayer.LayerSize.Width;
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
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];

            if (e.X - panel2.AutoScrollPosition.X < L.LayerSize.Width * TileSize.Width + L.OffSet.Width &&
                e.Y - panel2.AutoScrollPosition.Y < L.LayerSize.Height * TileSize.Height + L.OffSet.Height && e.X - panel2.AutoScrollPosition.X > L.OffSet.Width && e.Y - panel2.AutoScrollPosition.Y > L.OffSet.Height)
            {
                MouseLoc.Width = (e.X - panel2.AutoScrollPosition.X - L.OffSet.Width) / TileSize.Width;
                MouseLoc.Height = (e.Y - panel2.AutoScrollPosition.Y - L.OffSet.Height) / TileSize.Height;
                Point Temp = new Point(MouseLoc.Width, MouseLoc.Height);
                if (cmbMode.SelectedIndex < 0)
                {
                    for (int i = 0; i < cmbMode.Items.Count; i++)
                        if (i == cmbMode.Items.Count - 1 && cmbMode.Items[i].ToString() != cmbMode.Text)
                        {
                            cmbMode.Items.Add(cmbMode.Text);
                            cmbMode.SelectedIndex = cmbMode.Items.Count - 1;
                            break;
                        }
                        else if (cmbMode.Items[i].ToString() == cmbMode.Text)
                        {
                            cmbMode.SelectedIndex = i;
                            break;
                        }
                }
                if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "MAP_EDIT")
                {
                    if (bFill)
                    {
                        if (e.Button == MouseButtons.Left)
                        {
                            if (rFill.X == -1)
                            {
                                rFill.X = Temp.X;
                                rFill.Y = Temp.Y;
                            }
                            else if (rFill.Width == -1)
                            {
                                if (rFill.X > Temp.X)
                                {
                                    int nTemp = rFill.X;
                                    rFill.X = Temp.X;
                                    rFill.Width = nTemp + 1;
                                }
                                else
                                    rFill.Width = Temp.X + 1;
                                if (rFill.Y > Temp.Y)
                                {
                                    int nTemp = rFill.Y;
                                    rFill.Y = Temp.Y;
                                    rFill.Height = nTemp + 1;
                                }
                                else
                                    rFill.Height = Temp.Y + 1;
                            }
                            else
                            {
                                rFill = new Rectangle();
                                rFill.X = Temp.X;
                                rFill.Y = Temp.Y;
                            }
                        }
                        else
                        {
                            if (rFill.X != -1 && rFill.Width != -1)
                            {
                                myLayers Ls = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                                for (int x = rFill.X; x < rFill.Width; x++)
                                {
                                    for (int y = rFill.Y; y < rFill.Height; y++)
                                    {
                                        Ls.MyTiles[x, y].X = tileSelected.X;
                                        Ls.MyTiles[x, y].Y = tileSelected.Y;
                                    }
                                }
                                lstLayers.Items[lstLayers.SelectedIndex] = L;

                                rFill = new Rectangle(-1, -1, -1, -1);
                            }

                        }
                    }
                    if (e.Button == MouseButtons.Right)
                    {
                        if (bFill == false)
                        {

                            L.MyTiles[Temp.X, Temp.Y].X = -1;
                            L.MyTiles[Temp.X, Temp.Y].Y = -1;
                        }
                    }
                    else
                    {
                        if (bFill == false)
                        {
                            L.MyTiles[Temp.X, Temp.Y].X = tileSelected.X;
                            L.MyTiles[Temp.X, Temp.Y].Y = tileSelected.Y;
                        }
                    }
                }
                else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "EVENT")
                {
                    if (e.Button == MouseButtons.Right)
                    {
                        L.MyTiles[Temp.X, Temp.Y].EventType = "MAP_EDIT";
                    }
                    else
                    {
                        if (L.MyTiles[Temp.X, Temp.Y].EventType == "EVENT")
                            txtEventBroadCast.Text = L.MyTiles[Temp.X, Temp.Y].SzSpecial;
                        else
                        {
                            L.MyTiles[Temp.X, Temp.Y].EventType = "EVENT";
                            L.MyTiles[Temp.X, Temp.Y].SzSpecial = txtEventBroadCast.Text;
                        }
                    }
                }
                else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "BLOCK")
                {
                    if (e.Button == MouseButtons.Left)
                    {
                        if (bCreateRect)
                        {
                            if (e.X - panel2.AutoScrollPosition.X > rTemp.X)
                                rTemp.Width = e.Location.X - panel2.AutoScrollPosition.X - rTemp.X;
                            else
                            {
                                int nX = rTemp.X - e.X - panel2.AutoScrollPosition.X;
                                rTemp.X = e.X - panel2.AutoScrollPosition.X;
                                rTemp.Width = nX;
                            }
                            if (e.Y - panel2.AutoScrollPosition.Y > rTemp.Y)
                                rTemp.Height = e.Y - panel2.AutoScrollPosition.Y - rTemp.Y;
                            else
                            {
                                int nY = rTemp.Y - e.Y - panel2.AutoScrollPosition.Y;
                                rTemp.Y = e.Y - panel2.AutoScrollPosition.Y;
                                rTemp.Height = nY;
                            }
                            lstBlock.Items.Add(rTemp);
                            lstBlock.SelectedIndex++;
                            rTemp = new Rectangle();
                            bCreateRect = false;
                        }
                        else
                        {
                            bool bCollide = false;
                            for (int i = 0; i < lstBlock.Items.Count; i++)
                            {
                                rTemp = (Rectangle)lstBlock.Items[i];
                                if (e.X - panel2.AutoScrollPosition.X > rTemp.X && e.X - panel2.AutoScrollPosition.X < rTemp.Width + rTemp.X)
                                {
                                    if (e.Y - panel2.AutoScrollPosition.Y > rTemp.Y && e.Y - panel2.AutoScrollPosition.Y < rTemp.Height + rTemp.Y)
                                    {
                                        bCollide = true;
                                        lstBlock.SelectedIndex = i;
                                        break;
                                    }
                                }
                            }
                            if (bCollide)
                            {
                                nudBlockX.Value = rTemp.X;
                                nudBlockY.Value = rTemp.Y;
                                nudBlockHeight.Value = rTemp.Height;
                                nudBlockWidth.Value = rTemp.Width;
                            }
                            else
                            {
                                bCreateRect = true;
                                rTemp = new Rectangle();
                                rTemp.X = e.X - panel2.AutoScrollPosition.X;
                                rTemp.Y = e.Y - panel2.AutoScrollPosition.Y;
                            }
                        }
                    }
                    else
                    {
                        bool bCollide = false;
                        int nX = 0;
                        for (int i = 0; i < lstBlock.Items.Count; i++)
                        {
                            rTemp = (Rectangle)lstBlock.Items[i];
                            if (e.X - panel2.AutoScrollPosition.X > rTemp.X && e.X - panel2.AutoScrollPosition.X < rTemp.Width + rTemp.X)
                            {
                                if (e.Y - panel2.AutoScrollPosition.Y > rTemp.Y && e.Y - panel2.AutoScrollPosition.Y < rTemp.Height + rTemp.Y)
                                {
                                    nX = i;
                                    bCollide = true;
                                    break;
                                }
                            }
                        }
                        if (bCollide)
                            lstBlock.Items.RemoveAt(nX);

                        if (lstBlock.Items.Count < 1)
                            lstBlock.SelectedIndex = -1;
                    }

                }
                else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "WARP")
                {
                    if (e.Button == MouseButtons.Left)
                    {
                        if (L.MyTiles[Temp.X, Temp.Y].EventType != "WARP")
                        {
                            mapTile = Temp;
                            L.MyTiles[Temp.X, Temp.Y].EventType = cmbMode.Items[cmbMode.SelectedIndex].ToString();
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
                        L.MyTiles[Temp.X, Temp.Y].EventType = "MAP_EDIT";
                        L.MyTiles[Temp.X, Temp.Y].SzSpecial = "";
                        L.MyTiles[Temp.X, Temp.Y].WarpX = 0;
                        L.MyTiles[Temp.X, Temp.Y].WarpY = 0;
                    }
                }
                else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "NPCS")
                {
                    if (e.Button == MouseButtons.Left)
                    {

                        if (grpWayPoints.Visible)
                        {
                            if (radWPAdd.Checked)
                            {
                                L.MyTiles[mapTile.X, mapTile.Y].Waypoints.Add(new Point(Temp.X * TileSize.Width + TileSize.Width / 2, Temp.Y * TileSize.Height + TileSize.Height / 2));
                                lstWaypoints.Items.Add(new Point(Temp.X * TileSize.Width + TileSize.Width / 2, Temp.Y * TileSize.Height + TileSize.Height / 2));
                            }
                            else if (radWPMove.Checked)
                            {
                                if (lstWaypoints.SelectedIndex >= 0)
                                {
                                    Point ptTemp = (Point)lstWaypoints.Items[lstWaypoints.SelectedIndex];
                                    ptTemp = new Point(Temp.X * TileSize.Width + TileSize.Width / 2, Temp.Y * TileSize.Height + TileSize.Height / 2);

                                    lstWaypoints.Items[lstWaypoints.SelectedIndex] = ptTemp;
                                }
                            }
                        }
                        else
                        {
                            mapTile = Temp;
                            if (L.MyTiles[Temp.X, Temp.Y].EventType == "NPCS")
                            {
                                lstWaypoints.Items.Clear();
                                for (int i = 0; i < lstNPC.Items.Count; i++)
                                {
                                    if (lstNPC.Items[i].ToString() == L.MyTiles[Temp.X, Temp.Y].SzSpecial)
                                    {
                                        lstNPC.SelectedIndex = i;
                                        break;
                                    }

                                }
                                foreach (Point pt in L.MyTiles[Temp.X, Temp.Y].Waypoints)
                                {
                                    lstWaypoints.Items.Add(pt);
                                }
                                txtErase.Text = L.MyTiles[Temp.X, Temp.Y].SzErase;
                                txtBroadCast.Text = L.MyTiles[Temp.X, Temp.Y].BroadCast;
                            }
                            else
                            {
                                if (lstNPC.SelectedIndex >= 0)
                                {
                                    L.MyTiles[Temp.X, Temp.Y].EventType = "NPCS";
                                    L.MyTiles[Temp.X, Temp.Y].SzSpecial = lstNPC.Items[lstNPC.SelectedIndex].ToString();
                                    lstWaypoints.Items.Clear();
                                    L.MyTiles[Temp.X, Temp.Y].SzErase = txtErase.Text;
                                    L.MyTiles[Temp.X, Temp.Y].BroadCast = txtBroadCast.Text;
                                }
                            }

                        }
                    }
                    else
                    {
                        L.MyTiles[Temp.X, Temp.Y].EventType = "MAP_EDIT";
                        L.MyTiles[Temp.X, Temp.Y].SzSpecial = "";
                        L.MyTiles[Temp.X, Temp.Y].SzErase = "";
                        L.MyTiles[Temp.X, Temp.Y].BroadCast = "";
                        L.MyTiles[Temp.X, Temp.Y].Waypoints.Clear();
                        lstWaypoints.Items.Clear();
                    }
                }
                else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "CHESTS")
                {
                    if (e.Button == MouseButtons.Left)
                    {
                        if (L.MyTiles[Temp.X, Temp.Y].EventType == "CHESTS")
                        {
                            lstItems.Items.Clear();
                            foreach (myChest mc in L.MyTiles[Temp.X, Temp.Y].CItems)
                            {
                                lstItems.Items.Add(mc);
                            }
                            txtChestBroadcast.Text = L.MyTiles[Temp.X, Temp.Y].BroadCast;
                        }
                        else
                        {
                            L.MyTiles[Temp.X, Temp.Y].EventType = "CHESTS";
                            L.MyTiles[Temp.X, Temp.Y].SzSpecial = txtEventBroadCast.Text;
                            for (int i = 0; i < lstItems.Items.Count; i++)
                            {
                                myChest temp = (myChest)lstItems.Items[i];
                                L.MyTiles[Temp.X, Temp.Y].CItems.Add(temp);
                            }
                            L.MyTiles[Temp.X, Temp.Y].BroadCast = txtChestBroadcast.Text;
                        }
                    }
                    else
                    {
                        lstItems.Items.Clear();
                        L.MyTiles[Temp.X, Temp.Y].EventType = "MAP_EDIT";
                        L.MyTiles[Temp.X, Temp.Y].SzSpecial = "";
                        L.MyTiles[Temp.X, Temp.Y].BroadCast = "";
                        L.MyTiles[Temp.X, Temp.Y].CItems.Clear();

                    }
                }
                else
                {
                    if (e.Button == MouseButtons.Left)
                    {
                        if (L.MyTiles[Temp.X, Temp.Y].EventType != cmbMode.Items[cmbMode.SelectedIndex].ToString())
                        {
                            mapTile = Temp;
                            L.MyTiles[Temp.X, Temp.Y].EventType = cmbMode.Items[cmbMode.SelectedIndex].ToString();
                            L.MyTiles[Temp.X, Temp.Y].SzSpecial = txtEventBroadCast.Text;
                        }
                    }
                    else
                    {
                        L.MyTiles[Temp.X, Temp.Y].EventType = "MAP_EDIT";
                        L.MyTiles[Temp.X, Temp.Y].SzSpecial = "";
                        L.MyTiles[Temp.X, Temp.Y].WarpX = 0;
                        L.MyTiles[Temp.X, Temp.Y].BroadCast = "";
                        L.MyTiles[Temp.X, Temp.Y].SzErase = "";
                        L.MyTiles[Temp.X, Temp.Y].WarpY = 0;
                    }

                }
                lstLayers.Items[lstLayers.SelectedIndex] = L;
            }
        }

        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
            if (bCreateRect)
            {
                rTemp.Width = e.X - rTemp.X;
                rTemp.Height = e.Y - rTemp.Y;
            }

            if (e.X - panel2.AutoScrollPosition.X < L.LayerSize.Width * TileSize.Width + L.OffSet.Width &&
                e.Y - panel2.AutoScrollPosition.Y < L.LayerSize.Height * TileSize.Height + L.OffSet.Height && e.X - panel2.AutoScrollPosition.X > L.OffSet.Width && e.Y - panel2.AutoScrollPosition.Y > L.OffSet.Height)
            {
                MouseLoc.Width = (e.X - panel2.AutoScrollPosition.X - L.OffSet.Width) / TileSize.Width;
                MouseLoc.Height = (e.Y - panel2.AutoScrollPosition.Y - L.OffSet.Height) / TileSize.Height;
                Point Temp = new Point(MouseLoc.Width, MouseLoc.Height);
                if (cmbMode.SelectedIndex < 0)
                {
                    for (int i = 0; i < cmbMode.Items.Count; i++)
                        if (i == cmbMode.Items.Count - 1 && cmbMode.Items[i].ToString() != cmbMode.Text)
                        {
                            cmbMode.Items.Add(cmbMode.Text);
                            cmbMode.SelectedIndex = cmbMode.Items.Count - 1;
                            break;
                        }
                        else if (cmbMode.Items[i].ToString() == cmbMode.Text)
                        {
                            cmbMode.SelectedIndex = i;
                            break;
                        }
                }
                if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "MAP_EDIT")
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
                else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "BLOCK")
                {
                    if (mouseDown)
                    {
                        L.MyTiles[Temp.X, Temp.Y].EventType = cmbMode.Items[cmbMode.SelectedIndex].ToString();
                    }
                    else if (rmouseDown)
                    {
                        L.MyTiles[Temp.X, Temp.Y].EventType = "MAP_EDIT";
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
                myLayers Ls = (myLayers)lstLayers.Items[0];
                XElement xRoot = new XElement("World");
                XAttribute xWidth = new XAttribute("Width", Ls.LayerSize.Width);
                XAttribute xHeight = new XAttribute("Height", Ls.LayerSize.Height);
                XAttribute xTotalLayers = new XAttribute("Layers", lstLayers.Items.Count);
                XAttribute xTileWidth = new XAttribute("TileWidth", TileSize.Width);
                XAttribute xTileHeight = new XAttribute("TileHeight", TileSize.Height);
                XAttribute xImageLocation = new XAttribute("Image", szTileSetName);
                XAttribute xColorTrans = new XAttribute("Transparency", cTransparency.ToArgb());
                XAttribute xMusic = new XAttribute("Music", lblAudio.Text);
                if (lblAudio.Text != "Click to set Audio ----->")
                    xRoot.Add(xMusic);

                xRoot.Add(xWidth);
                xRoot.Add(xHeight);
                xRoot.Add(xTotalLayers);
                xRoot.Add(xTileWidth);
                xRoot.Add(xTileHeight);
                xRoot.Add(xImageLocation);
                xRoot.Add(xColorTrans);

                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    myLayers L = (myLayers)lstLayers.Items[nLayer];
                    XElement xLayer = new XElement("Layer");
                    XAttribute xID = new XAttribute("ID", nLayer);
                    XAttribute xLayerSizeWidth = new XAttribute("Width", L.LayerSize.Width);
                    XAttribute xLayerSizeHeight = new XAttribute("Height", L.LayerSize.Height);
                    XAttribute xLayerOffsetX = new XAttribute("Xoffset", L.OffSet.Width);
                    XAttribute xLayerOffsetY = new XAttribute("Yoffset", L.OffSet.Height);

                    xLayer.Add(xID);
                    xLayer.Add(xLayerSizeWidth);
                    xLayer.Add(xLayerSizeHeight);
                    xLayer.Add(xLayerOffsetX);
                    xLayer.Add(xLayerOffsetY);

                    xRoot.Add(xLayer);
                    for (int y = 0; y < L.LayerSize.Height; y++)
                    {

                        for (int x = 0; x < L.LayerSize.Width; x++)
                        {
                            XElement xTile = new XElement("Tile");
                            XAttribute xTileID = new XAttribute("ID", y * L.LayerSize.Width + x);
                            xTile.Add(xTileID);
                            xLayer.Add(xTile);
                            XAttribute xPosX = new XAttribute("posX", x);
                            XAttribute xPosY = new XAttribute("posY", y);
                            xTile.Add(xPosX);
                            xTile.Add(xPosY);
                            XElement xTileData = new XElement("Tile_Data");
                            XAttribute xTileX = new XAttribute("xTileID", L.MyTiles[x, y].X);
                            XAttribute xTileY = new XAttribute("yTileID", L.MyTiles[x, y].Y);
                            if (L.MyTiles[x, y].EventType == "CHESTS")
                            {
                                if (L.MyTiles[x, y].BroadCast != null && L.MyTiles[x, y].BroadCast != "")
                                {
                                    XAttribute xChestBroadCast = new XAttribute("EventBroad", L.MyTiles[x, y].BroadCast);
                                    xTileData.Add(xChestBroadCast);
                                }
                            }
                            if (L.MyTiles[x, y].EventType == "NPCS")
                            {
                                if (L.MyTiles[x, y].BroadCast != null && L.MyTiles[x, y].BroadCast != "")
                                {
                                    XAttribute xNPCBroadCast = new XAttribute("EventBroad", L.MyTiles[x, y].BroadCast);
                                    xTileData.Add(xNPCBroadCast);
                                }
                                if (L.MyTiles[x, y].SzErase != null && L.MyTiles[x, y].SzErase != "")
                                {
                                    XAttribute xNPCEraseCast = new XAttribute("RemoveEvent", L.MyTiles[x, y].SzErase);
                                    xTileData.Add(xNPCEraseCast);
                                }
                            }
                            if (L.MyTiles[x, y].EventType == null)
                                L.MyTiles[x, y].EventType = "MAP_EDIT";
                            XAttribute xTileEventType = new XAttribute("EventType", L.MyTiles[x, y].EventType);
                            XAttribute xTileWarpX = new XAttribute("WarpX", L.MyTiles[x, y].WarpX * nudTileWidth.Value);
                            XAttribute xTileWarpY = new XAttribute("WarpY", L.MyTiles[x, y].WarpY * nudTileHeight.Value);
                            if (L.MyTiles[x, y].SzSpecial == null)
                                L.MyTiles[x, y].SzSpecial = "";
                            XAttribute xEventId = new XAttribute("EventID", L.MyTiles[x, y].SzSpecial);
                            XAttribute xWayPointTotal = new XAttribute("Total_Waypoints", L.MyTiles[x, y].Waypoints.Count);

                            xTileData.Add(xTileX);
                            xTileData.Add(xTileY);
                            xTileData.Add(xEventId);
                            xTileData.Add(xTileEventType);
                            xTileData.Add(xTileWarpX);
                            xTileData.Add(xTileWarpY);

                            xTileData.Add(xWayPointTotal);

                            for (int j = 0; j < L.MyTiles[x, y].Waypoints.Count; j++)
                            {
                                XElement xWayPointData = new XElement("Waypoint");
                                XAttribute xWaypointPositionX = new XAttribute("X", L.MyTiles[x, y].Waypoints[j].X);
                                XAttribute xWaypointPositionY = new XAttribute("Y", L.MyTiles[x, y].Waypoints[j].Y);
                                xWayPointData.Add(xWaypointPositionX);
                                xWayPointData.Add(xWaypointPositionY);

                                xTileData.Add(xWayPointData);
                            }

                            if (L.MyTiles[x, y].EventType == "CHESTS")
                            {
                                for (int j = 0; j < L.MyTiles[x, y].CItems.Count; j++)
                                {
                                    XElement xChestData = new XElement("Chest");
                                    XAttribute xItemName = new XAttribute("Name", L.MyTiles[x, y].CItems[j].SzItem);
                                    XAttribute xHowMany = new XAttribute("Amount", L.MyTiles[x, y].CItems[j].HowMany);
                                    xChestData.Add(xItemName);
                                    xChestData.Add(xHowMany);

                                    xTileData.Add(xChestData);
                                }
                            }

                            xTile.Add(xTileData);
                        }
                    }
                }
                XElement xBlocked = new XElement("Block_Data");
                XAttribute xBTotal = new XAttribute("Total", lstBlock.Items.Count);
                xBlocked.Add(xBTotal);
                xRoot.Add(xBlocked);

                Rectangle r;
                for (int i = 0; i < lstBlock.Items.Count; i++)
                {
                    r = (Rectangle)lstBlock.Items[i];
                    XElement xBlock = new XElement("Block");
                    XAttribute xBlockX = new XAttribute("PosX", r.X);
                    XAttribute xBlockY = new XAttribute("PosY", r.Y);
                    XAttribute xBlockWidth = new XAttribute("Width", r.Width);
                    XAttribute xBlockHeight = new XAttribute("Height", r.Height);

                    xBlock.Add(xBlockX);
                    xBlock.Add(xBlockY);
                    xBlock.Add(xBlockWidth);
                    xBlock.Add(xBlockHeight);

                    xBlocked.Add(xBlock);
                    r = new Rectangle();
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
                myLayers Ls = (myLayers)lstLayers.Items[0];
                XElement xRoot = new XElement("World");
                XAttribute xWidth = new XAttribute("Width", Ls.LayerSize.Width);
                XAttribute xHeight = new XAttribute("Height", Ls.LayerSize.Height);
                XAttribute xTotalLayers = new XAttribute("Layers", lstLayers.Items.Count);
                XAttribute xTileWidth = new XAttribute("TileWidth", TileSize.Width);
                XAttribute xTileHeight = new XAttribute("TileHeight", TileSize.Height);
                XAttribute xImageLocation = new XAttribute("Image", szTileSetName);
                XAttribute xColorTrans = new XAttribute("Transparency", cTransparency.ToArgb());
                XAttribute xMusic = new XAttribute("Music", lblAudio.Text);
                if (lblAudio.Text != "Click to set Audio ----->")
                    xRoot.Add(xMusic);

                xRoot.Add(xWidth);
                xRoot.Add(xHeight);
                xRoot.Add(xTotalLayers);
                xRoot.Add(xTileWidth);
                xRoot.Add(xTileHeight);
                xRoot.Add(xImageLocation);
                xRoot.Add(xColorTrans);

                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    myLayers L = (myLayers)lstLayers.Items[nLayer];
                    XElement xLayer = new XElement("Layer");
                    XAttribute xID = new XAttribute("ID", nLayer);
                    XAttribute xLayerSizeWidth = new XAttribute("Width", L.LayerSize.Width);
                    XAttribute xLayerSizeHeight = new XAttribute("Height", L.LayerSize.Height);
                    XAttribute xLayerOffsetX = new XAttribute("Xoffset", L.OffSet.Width);
                    XAttribute xLayerOffsetY = new XAttribute("Yoffset", L.OffSet.Height);

                    xLayer.Add(xID);
                    xLayer.Add(xLayerSizeWidth);
                    xLayer.Add(xLayerSizeHeight);
                    xLayer.Add(xLayerOffsetX);
                    xLayer.Add(xLayerOffsetY);

                    xRoot.Add(xLayer);
                    for (int y = 0; y < L.LayerSize.Height; y++)
                    {

                        for (int x = 0; x < L.LayerSize.Width; x++)
                        {
                            XElement xTile = new XElement("Tile");
                            XAttribute xTileID = new XAttribute("ID", y * L.LayerSize.Width + x);
                            xTile.Add(xTileID);
                            xLayer.Add(xTile);
                            XAttribute xPosX = new XAttribute("posX", x);
                            XAttribute xPosY = new XAttribute("posY", y);
                            xTile.Add(xPosX);
                            xTile.Add(xPosY);
                            XElement xTileData = new XElement("Tile_Data");
                            XAttribute xTileX = new XAttribute("xTileID", L.MyTiles[x, y].X);
                            XAttribute xTileY = new XAttribute("yTileID", L.MyTiles[x, y].Y);
                            if (L.MyTiles[x, y].EventType == "CHESTS")
                            {
                                if (L.MyTiles[x, y].BroadCast != null && L.MyTiles[x, y].BroadCast != "")
                                {
                                    XAttribute xChestBroadCast = new XAttribute("EventBroad", L.MyTiles[x, y].BroadCast);
                                    xTileData.Add(xChestBroadCast);
                                }
                            }
                            if (L.MyTiles[x, y].EventType == "NPCS")
                            {
                                if (L.MyTiles[x, y].BroadCast != null && L.MyTiles[x, y].BroadCast != "")
                                {
                                    XAttribute xNPCBroadCast = new XAttribute("EventBroad", L.MyTiles[x, y].BroadCast);
                                    xTileData.Add(xNPCBroadCast);
                                }
                                if (L.MyTiles[x, y].SzErase != null && L.MyTiles[x, y].SzErase != "")
                                {
                                    XAttribute xNPCEraseCast = new XAttribute("RemoveEvent", L.MyTiles[x, y].SzErase);
                                    xTileData.Add(xNPCEraseCast);
                                }
                            }
                            if (L.MyTiles[x, y].EventType == null)
                                L.MyTiles[x, y].EventType = "MAP_EDIT";
                            XAttribute xTileEventType = new XAttribute("EventType", L.MyTiles[x, y].EventType);
                            XAttribute xTileWarpX = new XAttribute("WarpX", L.MyTiles[x, y].WarpX * nudTileWidth.Value);
                            XAttribute xTileWarpY = new XAttribute("WarpY", L.MyTiles[x, y].WarpY * nudTileHeight.Value);
                            if (L.MyTiles[x, y].SzSpecial == null)
                                L.MyTiles[x, y].SzSpecial = "";
                            XAttribute xEventId = new XAttribute("EventID", L.MyTiles[x, y].SzSpecial);
                            XAttribute xWayPointTotal;
                            if (L.MyTiles[x, y].Waypoints != null)
                                xWayPointTotal = new XAttribute("Total_Waypoints", L.MyTiles[x, y].Waypoints.Count);
                            else
                                xWayPointTotal = new XAttribute("Total_Waypoints", 0);

                            xTileData.Add(xTileX);
                            xTileData.Add(xTileY);
                            xTileData.Add(xEventId);
                            xTileData.Add(xTileEventType);
                            xTileData.Add(xTileWarpX);
                            xTileData.Add(xTileWarpY);
                            xTileData.Add(xWayPointTotal);
                            if (L.MyTiles[x, y].Waypoints != null)
                            {
                                for (int j = 0; j < L.MyTiles[x, y].Waypoints.Count; j++)
                                {
                                    XElement xWayPointData = new XElement("Waypoint");
                                    XAttribute xWaypointPositionX = new XAttribute("X", L.MyTiles[x, y].Waypoints[j].X);
                                    XAttribute xWaypointPositionY = new XAttribute("Y", L.MyTiles[x, y].Waypoints[j].Y);
                                    xWayPointData.Add(xWaypointPositionX);
                                    xWayPointData.Add(xWaypointPositionY);

                                    xTileData.Add(xWayPointData);
                                }
                            }

                            if (L.MyTiles[x, y].EventType == "CHESTS")
                            {
                                for (int j = 0; j < L.MyTiles[x, y].CItems.Count; j++)
                                {
                                    XElement xChestData = new XElement("Chest");
                                    XAttribute xItemName = new XAttribute("Name", L.MyTiles[x, y].CItems[j].SzItem);
                                    XAttribute xHowMany = new XAttribute("Amount", L.MyTiles[x, y].CItems[j].HowMany);
                                    xChestData.Add(xItemName);
                                    xChestData.Add(xHowMany);

                                    xTileData.Add(xChestData);
                                }
                            }

                            xTile.Add(xTileData);
                        }
                    }
                }

                XElement xBlocked = new XElement("Block_Data");
                XAttribute xBTotal = new XAttribute("Total", lstBlock.Items.Count);
                xBlocked.Add(xBTotal);
                xRoot.Add(xBlocked);

                Rectangle r;
                for (int i = 0; i < lstBlock.Items.Count; i++)
                {
                    r = (Rectangle)lstBlock.Items[i];
                    XElement xBlock = new XElement("Block");
                    XAttribute xBlockX = new XAttribute("PosX", r.X);
                    XAttribute xBlockY = new XAttribute("PosY", r.Y);
                    XAttribute xBlockWidth = new XAttribute("Width", r.Width);
                    XAttribute xBlockHeight = new XAttribute("Height", r.Height);

                    xBlock.Add(xBlockX);
                    xBlock.Add(xBlockY);
                    xBlock.Add(xBlockWidth);
                    xBlock.Add(xBlockHeight);

                    xBlocked.Add(xBlock);
                    r = new Rectangle();
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
                IEnumerable<XElement> xLayers = xRoot.Elements("Layer");

                XAttribute xMusic = xRoot.Attribute("Music");

                if (xMusic == null)
                    lblAudio.Text = "Click to set Audio ----->";
                else
                    lblAudio.Text = xMusic.Value;

                XAttribute xTotalLayers = xRoot.Attribute("Layers");
                XAttribute xTileWidth = xRoot.Attribute("TileWidth");
                XAttribute xTileHeight = xRoot.Attribute("TileHeight");
                XAttribute xTileImage = xRoot.Attribute("Image");
                XAttribute xColorTrans = xRoot.Attribute("Transparency");
                XAttribute xInitialSizeX = xRoot.Attribute("Width");
                XAttribute xInitialSizeY = xRoot.Attribute("Height");

                nudMapWidth.Maximum = 100;
                nudMapHeight.Maximum = 100;
                nudMapHeight.Value = nudMapHeight.Maximum;
                nudMapWidth.Value = nudMapWidth.Maximum;

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

                TileSize = new Size(Convert.ToInt32(xTileWidth.Value), Convert.ToInt32(xTileHeight.Value));
                lstLayers.Items.Clear();

                nudTileHeight.Value = TileSize.Height;
                nudTileWidth.Value = TileSize.Width;

                foreach (XElement Layers in xLayers)
                {
                    myLayers lTemp = new myLayers();
                    IEnumerable<XElement> xTiles = Layers.Elements();
                    XAttribute xWidth = Layers.Attribute("Width");
                    XAttribute xHeight = Layers.Attribute("Height");
                    XAttribute xOffsetX = Layers.Attribute("Xoffset");
                    XAttribute xOffsetY = Layers.Attribute("Yoffset");
                    lTemp.LayerSize = new Size(Convert.ToInt32(xWidth.Value), Convert.ToInt32(xHeight.Value));
                    lTemp.MyTiles = new myTile[Convert.ToInt32(xWidth.Value), Convert.ToInt32(xHeight.Value)];
                    lTemp.OffSet = new Size(Convert.ToInt32(xOffsetX.Value), Convert.ToInt32(xOffsetY.Value));
                    foreach (XElement xTile in xTiles)
                    {
                        XAttribute xPosX = xTile.Attribute("posX");
                        XAttribute xPosY = xTile.Attribute("posY");

                        XElement xTileInfo = xTile.Element("Tile_Data");
                        XAttribute xTileX = xTileInfo.Attribute("xTileID");
                        XAttribute xTileY = xTileInfo.Attribute("yTileID");
                        XAttribute xTileEventID = xTileInfo.Attribute("EventID");
                        XAttribute xTileEventType = xTileInfo.Attribute("EventType");
                        for (int i = 0; i < cmbMode.Items.Count; i++)
                        {
                            if (i == cmbMode.Items.Count - 1 && cmbMode.Items[i].ToString() != xTileEventType.Value)
                            {
                                cmbMode.Items.Add(xTileEventType.Value);
                                break;
                            }
                            else if (cmbMode.Items[i].ToString() == xTileEventType.Value)
                                break;
                        }
                        XAttribute xTileWarpX = xTileInfo.Attribute("WarpX");
                        XAttribute xTileWarpY = xTileInfo.Attribute("WarpY");

                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)] = new myTile();
                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].X = Convert.ToInt32(xTileX.Value);
                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].Y = Convert.ToInt32(xTileY.Value);
                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].WarpX = Convert.ToInt32(xTileWarpX.Value) / TileSize.Width;
                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].WarpY = Convert.ToInt32(xTileWarpY.Value) / TileSize.Height;
                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].SzSpecial = xTileEventID.Value;
                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].EventType = xTileEventType.Value;

                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].Waypoints = new List<Point>();

                        IEnumerable<XElement> xWaypoint = xTileInfo.Elements("Waypoint");
                        foreach (XElement wp in xWaypoint)
                        {
                            XAttribute xWPx = wp.Attribute("X");
                            XAttribute xWPy = wp.Attribute("Y");
                            int nWPx = Convert.ToInt32(xWPx.Value);
                            int nWPy = Convert.ToInt32(xWPy.Value);

                            lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].Waypoints.Add(new Point(nWPx, nWPy));
                        }
                        lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].CItems = new List<myChest>();


                        if (xTileEventType.Value == "NPCS")
                        {
                            XAttribute xNPCBroadCast = xTileInfo.Attribute("EventBroad");
                            XAttribute xNPCEraseCast = xTileInfo.Attribute("RemoveEvent");
                            if (xNPCBroadCast != null)
                                lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].BroadCast = xNPCBroadCast.Value;

                            if (xNPCEraseCast != null)
                                lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].SzErase = xNPCEraseCast.Value;
                        }


                        if (xTileEventType.Value == "CHESTS")
                        {
                            XAttribute xChestBroadCast = xTileInfo.Attribute("EventBroad");
                            if (xChestBroadCast.Value != null)
                                lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].BroadCast = xChestBroadCast.Value;

                            IEnumerable<XElement> xChests = xTileInfo.Elements("Chest");
                            foreach (XElement ch in xChests)
                            {
                                XAttribute xItemName = ch.Attribute("Name");
                                XAttribute xAmount = ch.Attribute("Amount");
                                myChest tempChest = new myChest();

                                tempChest.SzItem = xItemName.Value;
                                tempChest.HowMany = Convert.ToDecimal(xAmount.Value);

                                lTemp.MyTiles[Convert.ToInt32(xPosX.Value), Convert.ToInt32(xPosY.Value)].CItems.Add(tempChest);
                            }

                        }
                    }
                    lstLayers.Items.Add(lTemp);
                }

                XElement xBlocked = xRoot.Element("Block_Data");

                IEnumerable<XElement> xBlock = xBlocked.Elements();
                Rectangle r;
                foreach (XElement xBData in xBlock)
                {
                    r = new Rectangle();
                    XAttribute xBlockX = xBData.Attribute("PosX");
                    XAttribute xBlockY = xBData.Attribute("PosY");
                    XAttribute xBlockWidth = xBData.Attribute("Width");
                    XAttribute xBlockHeight = xBData.Attribute("Height");

                    r.X = Convert.ToInt32(xBlockX.Value);
                    r.Y = Convert.ToInt32(xBlockY.Value);
                    r.Width = Convert.ToInt32(xBlockWidth.Value);
                    r.Height = Convert.ToInt32(xBlockHeight.Value);

                    lstBlock.Items.Add(r);
                }
                szFileName = dlg.FileName;
            }

            lstLayers.SelectedIndex = lstLayers.Items.Count - 1;
            myLayers Ls = (myLayers)lstLayers.Items[0];
            panel2.AutoScrollMinSize = new Size(Ls.LayerSize.Width * TileSize.Width, Ls.LayerSize.Height * TileSize.Height);
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
            if (bFill)
                bFill = false;
            else
                bFill = true;
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

        private void chkMoves_CheckedChanged(object sender, EventArgs e)
        {
            btnNPCMove.Enabled = chkMoves.Checked;
            if (grpWayPoints.Visible && !chkMoves.Checked)
                grpWayPoints.Visible = false;
        }

        private void btnNpcAdd_Click(object sender, EventArgs e)
        {

            btnNpcApply.Enabled = false;
            btnNpcCancel.Enabled = false;
        }

        private void btnNpcCancel_Click(object sender, EventArgs e)
        {
            btnNpcApply.Enabled = false;
            btnNpcCancel.Enabled = false;
        }

        private void btnNpcApply_Click(object sender, EventArgs e)
        {
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
            lTemp.LayerSize = new Size(5, 5);
            lTemp.OffSet = new Size(0, 0);
            lTemp.MyTiles = new myTile[5, 5];

            for (int y = 0; y < lTemp.LayerSize.Height; y++)
            {
                for (int x = 0; x < lTemp.LayerSize.Width; x++)
                {
                    lTemp.MyTiles[x, y].X = -1;
                    lTemp.MyTiles[x, y].Y = -1;
                    lTemp.MyTiles[x, y].Waypoints = new List<Point>();
                    lTemp.MyTiles[x, y].CItems = new List<myChest>();

                }
            }

            lstLayers.Items.Add(lTemp);
            lstLayers.SelectedIndex = lstLayers.Items.Count - 1;
            nudMapHeight.Value = 5;
            nudMapWidth.Value = 5;
            btnDelete.Enabled = true;
        }

        private void btnShiftDown_Click(object sender, EventArgs e)
        {
            myLayers l = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
            lstLayers.Items[lstLayers.SelectedIndex] = lstLayers.Items[lstLayers.SelectedIndex + 1];
            lstLayers.Items[lstLayers.SelectedIndex + 1] = l;
            lstLayers.SelectedIndex++;
        }

        private void lstLayers_SelectedIndexChanged(object sender, EventArgs e)
        {
            bChangedLayers = true;
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
            nudMapHeight.Value = L.LayerSize.Height;
            nudMapWidth.Value = L.LayerSize.Width;
            nudXOffset.Value = L.OffSet.Width;
            nudYOffset.Value = L.OffSet.Height;
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];

            for (int y = 0; y < L.LayerSize.Height; y++)
            {
                for (int x = 0; x < L.LayerSize.Width; x++)
                {
                    L.MyTiles[x, y].X = -1;
                    L.MyTiles[x, y].Y = -1;
                }
            }
            lstLayers.Items[lstLayers.SelectedIndex] = L;
        }

        private void cmbMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbMode.SelectedIndex < 0)
            {
                cmbMode.Items.Add(cmbMode.SelectedText);
            }
            selectedNPC = new myNPC();
            selectedNPC.Units = new List<myUnits>();
            selectedNPC.Waypoints = new List<Point>();

            grpWarp.Visible = false;
            grpNPC.Visible = false;
            grpWayPoints.Visible = false;
            grpBlock.Visible = false;
            grpChest.Visible = false;
            lstUnits.Items.Clear();
            lstWaypoints.Items.Clear();
            bCreateRect = false;
            rTemp = new Rectangle();
            if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "WARP")
            {
                grpWarp.Visible = true;

            }
            else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "NPCS")
            {
                grpNPC.Visible = true;
                if (chkMoves.Checked)
                    grpWayPoints.Visible = true;
            }
            else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "BLOCK")
            {
                grpBlock.Visible = true;
            }
            else if (cmbMode.Items[cmbMode.SelectedIndex].ToString() == "CHESTS")
            {
                grpChest.Visible = true;
            }

        }

        private void btnShiftUp_Click(object sender, EventArgs e)
        {
            myLayers l = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
            lstLayers.Items[lstLayers.SelectedIndex] = lstLayers.Items[lstLayers.SelectedIndex - 1];
            lstLayers.Items[lstLayers.SelectedIndex - 1] = l;
            lstLayers.SelectedIndex--;
        }

        private void Form1_Resize(object sender, EventArgs e)
        {

        }

        private void btnNPCUnits_Click(object sender, EventArgs e)
        {

        }

        private void nudXOffset_ValueChanged(object sender, EventArgs e)
        {
            if (lstLayers.SelectedIndex != 0)
            {
                myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                L.OffSet = new Size(Convert.ToInt32(nudXOffset.Value), Convert.ToInt32(nudYOffset.Value));
                lstLayers.Items[lstLayers.SelectedIndex] = L;
            }
        }

        private void lstBlock_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstBlock.SelectedIndex < 0)
            {
                nudBlockHeight.Enabled = false;
                nudBlockWidth.Enabled = false;
                nudBlockX.Enabled = false;
                nudBlockY.Enabled = false;
            }
            else
            {

                nudBlockHeight.Enabled = true;
                nudBlockWidth.Enabled = true;
                nudBlockX.Enabled = true;
                nudBlockY.Enabled = true;

                Rectangle r = (Rectangle)lstBlock.Items[lstBlock.SelectedIndex];
                nudBlockHeight.Value = r.Height;
                nudBlockWidth.Value = r.Width;
                nudBlockX.Value = r.X;
                nudBlockY.Value = r.Y;
            }
        }

        private void nudBlockX_ValueChanged(object sender, EventArgs e)
        {
            if (lstBlock.SelectedIndex >= 0)
            {
                Rectangle r = (Rectangle)lstBlock.Items[lstBlock.SelectedIndex];

                r.Height = Convert.ToInt32(nudBlockHeight.Value);
                r.Width = Convert.ToInt32(nudBlockWidth.Value);
                r.X = Convert.ToInt32(nudBlockX.Value);
                r.Y = Convert.ToInt32(nudBlockY.Value);

                lstBlock.Items[lstBlock.SelectedIndex] = r;
            }
        }

        private void nudMapWidth_ValueChanged(object sender, EventArgs e)
        {
            if (bChangedLayers == false)
            {
                myLayers l = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    myLayers tLayer = new myLayers();
                    tLayer.LayerSize = new Size(Convert.ToInt32(nudMapWidth.Value), Convert.ToInt32(nudMapHeight.Value));
                    tLayer.MyTiles = new myTile[Convert.ToInt32(nudMapWidth.Value), Convert.ToInt32(nudMapHeight.Value)];
                    myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                    tLayer.OffSet = L.OffSet;
                    for (int x = 0; x < tLayer.LayerSize.Width; x++)
                    {
                        for (int y = 0; y < tLayer.LayerSize.Height; y++)
                        {
                            if (y < L.LayerSize.Height && x < L.LayerSize.Width)
                                tLayer.MyTiles[x, y] = L.MyTiles[x, y];
                            else
                            {
                                if (x < Convert.ToInt32(nudMapWidth.Value) && y < Convert.ToInt32(nudMapHeight.Value))
                                {
                                    tLayer.MyTiles[x, y].X = -1;
                                    tLayer.MyTiles[x, y].Y = -1;
                                    tLayer.MyTiles[x, y].Waypoints = new List<Point>();
                                    tLayer.MyTiles[x, y].CItems = new List<myChest>();
                                }
                            }
                        }
                    }
                    lstLayers.Items[lstLayers.SelectedIndex] = tLayer;
                }
                myLayers Ls = (myLayers)lstLayers.Items[0];
                panel2.AutoScrollMinSize = new Size(Ls.LayerSize.Width * TileSize.Width, Ls.LayerSize.Height * TileSize.Height);
            }
            bChangedLayers = false;
        }

        private void nudMapHeight_ValueChanged(object sender, EventArgs e)
        {
            if (bChangedLayers == false)
            {
                myLayers l = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                for (int nLayer = 0; nLayer < lstLayers.Items.Count; nLayer++)
                {
                    myLayers tLayer = new myLayers();
                    tLayer.LayerSize = new Size(Convert.ToInt32(nudMapWidth.Value), Convert.ToInt32(nudMapHeight.Value));
                    tLayer.MyTiles = new myTile[Convert.ToInt32(nudMapWidth.Value), Convert.ToInt32(nudMapHeight.Value)];
                    myLayers L = (myLayers)lstLayers.Items[lstLayers.SelectedIndex];
                    tLayer.OffSet = L.OffSet;
                    for (int x = 0; x < tLayer.LayerSize.Width; x++)
                    {
                        for (int y = 0; y < tLayer.LayerSize.Height; y++)
                        {
                            if (y < L.LayerSize.Height && x < L.LayerSize.Width)
                                tLayer.MyTiles[x, y] = L.MyTiles[x, y];
                            else
                            {
                                if (x < Convert.ToInt32(nudMapWidth.Value) && y < Convert.ToInt32(nudMapHeight.Value))
                                {
                                    tLayer.MyTiles[x, y].X = -1;
                                    tLayer.MyTiles[x, y].Y = -1;
                                    tLayer.MyTiles[x, y].Waypoints = new List<Point>();
                                    tLayer.MyTiles[x, y].CItems = new List<myChest>();
                                }
                            }
                        }
                    }
                    lstLayers.Items[lstLayers.SelectedIndex] = tLayer;
                }
                myLayers Ls = (myLayers)lstLayers.Items[0];
                panel2.AutoScrollMinSize = new Size(Ls.LayerSize.Width * TileSize.Width, Ls.LayerSize.Height * TileSize.Height);
            }
            bChangedLayers = false;
        }

        private void lstUnits_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstUnits.SelectedIndex != -1)
                btnApply.Enabled = true;
            else
                btnApply.Enabled = false;

        }

        private void btnAddUnit_Click(object sender, EventArgs e)
        {

        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            btnApply.Enabled = false;
            btnNpcCancel.Enabled = false;
        }

        private void btnDeleteUnit_Click(object sender, EventArgs e)
        {
            if (lstUnits.SelectedIndex != -1)
                lstUnits.Items.RemoveAt(lstUnits.SelectedIndex);
        }

        private void lstAnimations_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnApply.Enabled = true;
            btnNpcCancel.Enabled = true;
        }

        private void chkMoves_CheckedChanged_1(object sender, EventArgs e)
        {
            btnNPCMove.Enabled = chkMoves.Checked;
            if (!chkMoves.Checked)
                lstWaypoints.Items.Clear();
        }

        private void createNewNPCToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ModalNpc nEdit = new ModalNpc();
            if (DialogResult.OK == nEdit.ShowDialog())
            {
                lstNPC.Items.Clear();
                foreach (string szMapID in Directory.GetFiles(Environment.CurrentDirectory + "\\..\\Assets\\Data\\NPCS\\", "*.xml").Select(Path.GetFileName))
                {
                    string szTemp = szMapID.Remove(szMapID.Length - 4, 4);
                    lstNPC.Items.Add(szTemp);
                }
            }
        }

        private void btnAddItem_Click(object sender, EventArgs e)
        {
            if (cmbItemChoice.SelectedIndex >= 0)
            {
                myChest temp = new myChest();
                temp.SzItem = cmbItemChoice.Items[cmbItemChoice.SelectedIndex].ToString();
                temp.HowMany = nudItems.Value;

                lstItems.Items.Add(temp);
                cmbItemChoice.SelectedIndex = 0;
                nudItems.Value = 1;
                lstItems.SelectedIndex = -1;
            }
        }

        private void btnItemApply_Click(object sender, EventArgs e)
        {
            if (lstItems.SelectedIndex >= 0)
            {
                myChest temp = (myChest)lstItems.Items[lstItems.SelectedIndex];
                temp.SzItem = cmbItemChoice.Items[cmbItemChoice.SelectedIndex].ToString();
                temp.HowMany = nudItems.Value;
                lstItems.Items[lstItems.SelectedIndex] = temp;

                nudItems.Value = 1;
                cmbItemChoice.SelectedIndex = 0;
                lstItems.SelectedIndex = -1;
            }
        }

        private void btnDelItem_Click(object sender, EventArgs e)
        {
            if (lstItems.SelectedIndex >= 0)
            {
                lstItems.Items.RemoveAt(lstItems.SelectedIndex);
                lstItems.SelectedIndex = -1;
            }
        }

        private void btnSound_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            string temp = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\assets\\Audio\\Music");
            ofd.InitialDirectory = temp;
            ofd.Filter = "All Files|*.*";
            ofd.FilterIndex = 1;

            if (DialogResult.OK == ofd.ShowDialog())
            {
                lblAudio.Text = Path.GetFileName(ofd.FileName);
            }
        }
    }

}
