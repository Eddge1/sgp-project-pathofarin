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
        bool bMapEdit = true;
        string szFileName;
        string szRelativePath;
        string szTileSetName;
        bool looping = true;
        bool ShowGrid = true;
        bool mouseDown = false;
        bool rmouseDown = false;
        Color cTransparency = Color.Magenta;

        Size MapSize = new Size(5, 5);
        Size TileSize = new Size(64, 64);
        Size TileSet = new Size(4, 4);
        Size MouseLoc = new Size(0, 0);
        Point tileSelected = new Point(0, 0);

        int imageID = -1;
        int TotalLayers = 1;
        struct myTile
        {
            int x;
            int y;
            bool isBlocked;
            bool isEvent;
            bool isNPC;
            string szSpecial;

            public int X
            {
                get { return x; }
                set { x = value; }
            }

            public int Y
            {
                get { return y; }
                set { y = value; }
            }

            public bool IsBlocked
            {
                get { return isBlocked; }
                set { isBlocked = value; }
            }

            public bool IsEvent
            {
                get { return isEvent; }
                set { isEvent = value; }
            }

            public bool IsNPC
            {
                get { return isNPC; }
                set { isNPC = value; }
            }

            public string SzSpecial
            {
                get { return szSpecial; }
                set { szSpecial = value; }
            }

        }

        struct myLayers
        {
            Point[,] myTiles;

            public Point[,] MyTiles
            {
                get { return myTiles; }
                set { myTiles = value; }
            }

        };


        struct myWorld
        {
            List<myLayers> theWorld;

            public List<myLayers> TheWorld
            {
                get { return theWorld; }
                set { theWorld = value; }
            }

        };

        myWorld currMap = new myWorld();
        myLayers tempLayer = new myLayers();
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

            if (nudLayer.Value < 1)
                nudLayer.Value = 1;

            if (nudLayer.Value > TotalLayers)
            {
                tempLayer.MyTiles = new Point[MapSize.Width, MapSize.Height];

                currMap.TheWorld.Add(tempLayer);
                TotalLayers = currMap.TheWorld.Count;
                label1.Text = "of " + currMap.TheWorld.Count.ToString();
            }


            if (MapSize.Width != Convert.ToInt32(nudMapWidth.Value) || MapSize.Height != Convert.ToInt32(nudMapHeight.Value))
            {
                for (int nLayer = 0; nLayer < currMap.TheWorld.Count(); nLayer++)
                {
                    myLayers tLayer = new myLayers();
                    tLayer.MyTiles = new Point[Convert.ToInt32(nudMapWidth.Value), Convert.ToInt32(nudMapHeight.Value)];
                    for (int x = 0; x < MapSize.Width; x++)
                    {
                        if (x < nudMapWidth.Value)
                        {
                            for (int y = 0; y < MapSize.Height; y++)
                            {
                                if (y < nudMapHeight.Value)
                                    tLayer.MyTiles[x, y] = currMap.TheWorld[nLayer].MyTiles[x, y];
                            }
                        }
                    }
                    currMap.TheWorld[nLayer] = tLayer;
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
                for (int nLayer = 0; nLayer < nudLayer.Value; nLayer++)
                {
                    for (int y = 0; y < MapSize.Height; y++)
                    {
                        for (int x = 0; x < MapSize.Width; x++)
                        {
                            TM.Draw(imageID, x * TileSize.Width + panel2.AutoScrollPosition.X, y * TileSize.Height + panel2.AutoScrollPosition.Y, 1, 1,
                                new Rectangle((currMap.TheWorld[nLayer].MyTiles[x, y].X % TileSize.Width) * TileSize.Width,
                                    (currMap.TheWorld[nLayer].MyTiles[x, y].Y % TileSize.Height) * TileSize.Height,
                                TileSize.Width, TileSize.Height));
                        }
                    }
                }

                if (bMapEdit)
                    TM.Draw(imageID, MouseLoc.Width * TileSize.Width, MouseLoc.Height * TileSize.Height, 1, 1, new Rectangle(tileSelected.X * TileSize.Width + panel2.AutoScrollPosition.X, tileSelected.Y * TileSize.Height + panel2.AutoScrollPosition.Y, TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(127, 255, 255, 255));
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

            DX.SpriteEnd();
            DX.DeviceEnd();
            DX.Present();
        }

        public void Initialize()
        {
            szRelativePath = Environment.CurrentDirectory + "\\Assets\\Graphics\\Tilesets\\";
            szTileSetName = "";
            szFileName = "";

            DX.Initialize(panel2, false);
            DX.AddRenderTarget(panel1);

            if (imageID != -1)
                TM.UnloadTexture(imageID);

            imageID = -1;

            TM.Initialize(DX.Device, DX.Sprite);



            currMap.TheWorld = new List<myLayers>();
            tempLayer.MyTiles = new Point[MapSize.Width, MapSize.Height];

            currMap.TheWorld.Clear();
            currMap.TheWorld.Add(tempLayer);

            TotalLayers = currMap.TheWorld.Count;

            label1.Text = "of " + currMap.TheWorld.Count.ToString();

            TileSize.Height = 32;
            TileSize.Width = 32;

            nudTileHeight.Value = TileSize.Height;
            nudTileWidth.Value = TileSize.Width;
            nudLayer.Value = TotalLayers;

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
            if (bMapEdit)
            {
                if (e.Button == MouseButtons.Right)
                {
                    if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height && e.X > 0 && e.Y > 0)
                    {
                        Point Temp = new Point((e.X - panel2.AutoScrollPosition.X) / TileSize.Width, (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);
                        currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[Temp.X, Temp.Y] = new Point(0, 0);
                    }
                }
                else
                    if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height)
                    {
                        if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height && e.X > 0 && e.Y > 0)
                        {
                            Point Temp = new Point((e.X - panel2.AutoScrollPosition.X) / TileSize.Width, (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);
                            currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[Temp.X, Temp.Y] = tileSelected;
                        }
                    }
            }
            else
            {





            }
        }

        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {
            MouseLoc.Width = (e.X - panel2.AutoScrollPosition.X) / TileSize.Width;
            MouseLoc.Height = (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height;
            if (bMapEdit)
            {
                if (mouseDown)
                {
                    if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height && e.X > 0 && e.Y > 0)
                    {
                        int nTempX = (e.X - panel2.AutoScrollPosition.X) / TileSize.Width;
                        int nTempY = ((e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);

                        if (nTempX >= 0 && nTempY >= 0 && nTempX < MapSize.Width && nTempY < MapSize.Height)
                            currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[nTempX, nTempY] = tileSelected;
                    }
                }
                else if (rmouseDown)
                {
                    if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height && e.X > 0 && e.Y > 0)
                    {
                        Point Temp = new Point((e.X - panel2.AutoScrollPosition.X) / TileSize.Width, (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);
                        currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[Temp.X, Temp.Y] = new Point(0, 0);
                    }
                }
            }
            else
            {


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
                XAttribute xTotalLayers = new XAttribute("Layers", currMap.TheWorld.Count);
                XAttribute xTileWidth = new XAttribute("TileWidth", TileSize.Width);
                XAttribute xTileHeight = new XAttribute("TileHeight", TileSize.Height);
                XAttribute xImageLocation = new XAttribute("Image", szTileSetName);

                xRoot.Add(xWidth);
                xRoot.Add(xHeight);
                xRoot.Add(xTotalLayers);
                xRoot.Add(xTileWidth);
                xRoot.Add(xTileHeight);
                xRoot.Add(xImageLocation);

                for (int nLayer = 0; nLayer < currMap.TheWorld.Count; nLayer++)
                {
                    XElement xLayer = new XElement("Layer");
                    XAttribute xID = new XAttribute("ID", nLayer);
                    xLayer.Add(xID);
                    xRoot.Add(xLayer);
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
                            XElement xX = new XElement("Tile_Data");
                            XAttribute xTileX = new XAttribute("xTileID", currMap.TheWorld[nLayer].MyTiles[x, y].X);
                            XAttribute xTileY = new XAttribute("yTileID", currMap.TheWorld[nLayer].MyTiles[x, y].Y);
                            xX.Add(xTileX);
                            xX.Add(xTileY);
                            xTile.Add(xX);
                        }
                    }
                }
                xRoot.Save(szFileName);

            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "All Files|*.*|XML Files|*.xml";
            dlg.FilterIndex = 2;
            dlg.DefaultExt = "xml";

            if (DialogResult.OK == dlg.ShowDialog())
            {
                XElement xRoot = new XElement("World");
                XAttribute xWidth = new XAttribute("Width", MapSize.Width);
                XAttribute xHeight = new XAttribute("Height", MapSize.Height);
                XAttribute xTotalLayers = new XAttribute("Layers", currMap.TheWorld.Count);
                XAttribute xTileWidth = new XAttribute("TileWidth", TileSize.Width);
                XAttribute xTileHeight = new XAttribute("TileHeight", TileSize.Height);
                XAttribute xImageLocation = new XAttribute("Image", szTileSetName);

                xRoot.Add(xWidth);
                xRoot.Add(xHeight);
                xRoot.Add(xTotalLayers);
                xRoot.Add(xTileWidth);
                xRoot.Add(xTileHeight);
                xRoot.Add(xImageLocation);

                for (int nLayer = 0; nLayer < currMap.TheWorld.Count; nLayer++)
                {
                    XElement xLayer = new XElement("Layer");
                    XAttribute xID = new XAttribute("ID", nLayer);
                    xLayer.Add(xID);
                    xRoot.Add(xLayer);
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
                            XElement xX = new XElement("Tile_Data");
                            XAttribute xTileX = new XAttribute("xTileID", currMap.TheWorld[nLayer].MyTiles[x, y].X);
                            XAttribute xTileY = new XAttribute("yTileID", currMap.TheWorld[nLayer].MyTiles[x, y].Y);
                            xX.Add(xTileX);
                            xX.Add(xTileY);
                            xTile.Add(xX);
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
            Initialize();
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|XML Files|*.xml";
            dlg.FilterIndex = 2;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                XElement xRoot = XElement.Load(dlg.FileName);
                IEnumerable<XElement> xLayers = xRoot.Elements();

                XAttribute xWidth = xRoot.Attribute("Width");
                XAttribute xHeight = xRoot.Attribute("Height");
                XAttribute xTotalLayers = xRoot.Attribute("Layers");
                XAttribute xTileWidth = xRoot.Attribute("TileWidth");
                XAttribute xTileHeight = xRoot.Attribute("TileHeight");
                XAttribute xTileImage = xRoot.Attribute("Image");

                if (xTileImage.Value.ToString() != "")
                {
                    szTileSetName = xTileImage.Value.ToString();
                    imageID = TM.LoadTexture(szRelativePath + szTileSetName);
                    panel1.AutoScrollMinSize = new Size(TM.GetTextureWidth(imageID), TM.GetTextureHeight(imageID));
                }
                else
                {
                    imageID = -1;
                    panel1.AutoScrollMinSize = new Size(panel1.ClientSize.Width, panel1.ClientSize.Height);
                }

                MapSize = new Size(Convert.ToInt32(xWidth.Value), Convert.ToInt32(xHeight.Value));
                TileSize = new Size(Convert.ToInt32(xTileWidth.Value), Convert.ToInt32(xTileHeight.Value));

                myLayers lTemp = new myLayers();
                lTemp.MyTiles = new Point[MapSize.Width, MapSize.Height];
                currMap.TheWorld = new List<myLayers>();

                nudLayer.Value = 1;
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
                        Point pTile = new Point(Convert.ToInt32(xTileX.Value), Convert.ToInt32(xTileY.Value));

                        lTemp.MyTiles[nPosX, nPosY] = pTile;
                    }
                    currMap.TheWorld.Add(lTemp);
                    lTemp.MyTiles = new Point[MapSize.Width, MapSize.Height];
                }
                szFileName = dlg.FileName;
            }
            label1.Text = "of " + currMap.TheWorld.Count.ToString();
            panel2.AutoScrollMinSize = new Size(MapSize.Width * TileSize.Width, MapSize.Height * TileSize.Height);
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
            if (imageID != -1)
                TM.UnloadTexture(imageID);
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*";
            dlg.FilterIndex = 2;

            if (DialogResult.OK == dlg.ShowDialog())
            {

                szTileSetName = Path.GetFileName(dlg.FileName);
                if (!File.Exists(szRelativePath + szTileSetName))
                    File.Copy(dlg.FileName, szRelativePath + szTileSetName);

                imageID = TM.LoadTexture(szRelativePath + szTileSetName);
                panel1.AutoScrollMinSize = new Size(TM.GetTextureWidth(imageID), TM.GetTextureHeight(imageID));
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

    }
}
