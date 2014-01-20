using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SGP;

namespace SGP_PoA_LevelEditor
{
    public partial class Form1 : Form
    {
        bool looping = true;
        bool ShowGrid = true;
        bool mouseDown = false;
        Color cTransparency;

        Size MapSize = new Size(5, 5);
        Size TileSize = new Size(64, 64);
        Size TileSet = new Size(4, 4);
        Size MouseLoc = new Size(0, 0);
        Point tileSelected = new Point(0, 0);

        int imageID = -1;
        int TotalLayers = 1;

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

            if (TileSet.Width != Convert.ToInt32(nudTileWidth.Value))
            {
                TileSize.Width = Convert.ToInt32(nudTileWidth.Value);
                TileSet.Width = TM.GetTextureWidth(imageID) / TileSize.Width;
            }
            if (TileSet.Height != Convert.ToInt32(nudTileHeight.Value))
            {
                TileSize.Height = Convert.ToInt32(nudTileHeight.Value);
                TileSet.Height = TM.GetTextureHeight(imageID) / TileSize.Height;
            }

            if (nudLayer.Value < 1)
                nudLayer.Value = 1;

            if (nudLayer.Value > TotalLayers)
            {
                tempLayer.MyTiles = new Point[MapSize.Width, MapSize.Height];

                /////////////////////////////////////////////////////////////

                currMap.TheWorld.Add(tempLayer);
                TotalLayers = currMap.TheWorld.Count;
            }


            if (MapSize.Width != Convert.ToInt32(nudMapWidth.Value))
            {
                ///////////////////////////////////////////////////////
            }
            else if (MapSize.Height != Convert.ToInt32(nudMapWidth.Value))
            {
                ////////////////////////////////////////////////////////
            }
        }

        public void Render()
        {
            DX.Clear(panel2, Color.Magenta);
            DX.DeviceBegin();
            DX.SpriteBegin();

            for (int nLayer = 0; nLayer < nudLayer.Value; nLayer++)
            {
                for (int y = 0; y < MapSize.Height; y++)
                {
                    for (int x = 0; x < MapSize.Width; x++)
                    {
                        TM.Draw(imageID, x * TileSize.Width, y * TileSize.Height, 1, 1,
                            new Rectangle((currMap.TheWorld[nLayer].MyTiles[x, y].X % TileSize.Width) * TileSize.Width,(currMap.TheWorld[nLayer].MyTiles[x, y].Y % TileSize.Height) * TileSize.Height,
                            TileSize.Width, TileSize.Height));
                    }
                }
            }

            TM.Draw(imageID, MouseLoc.Width * TileSize.Width, MouseLoc.Height * TileSize.Height, 1, 1, new Rectangle(tileSelected.X * TileSize.Width, tileSelected.Y * TileSize.Height, TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(127, 255, 255, 255));

            if (ShowGrid)
            {
                for (int i = 0; i < (MapSize.Width * MapSize.Height); i++)
                {
                    DX.DrawHollowRect(new Rectangle((i % MapSize.Width) * TileSize.Width, (i / MapSize.Height) * TileSize.Height, TileSize.Width, TileSize.Height), Color.White, 1);
                }
            }

            DX.SpriteEnd();
            DX.DeviceEnd();
            DX.Present();

            DX.Clear(panel1, Color.Black);
            DX.DeviceBegin();
            DX.SpriteBegin();

            TM.Draw(imageID, panel1.AutoScrollPosition.X, panel1.AutoScrollPosition.Y);

            if (ShowGrid)
            {
                for (int i = 0; i < (TileSet.Width * TileSet.Height); i++)
                {
                    DX.DrawHollowRect(new Rectangle((i % TileSet.Width) * TileSize.Width + panel1.AutoScrollPosition.X, (i / TileSet.Height) * TileSize.Height + panel1.AutoScrollPosition.Y, TileSize.Width, TileSize.Height), Color.White, 1);
                }
            }

            /*
             Draw the Tileset here
            */

            DX.SpriteEnd();
            DX.DeviceEnd();
            DX.Present();
        }

        public void Initialize()
        {
            DX.Initialize(panel2, false);
            DX.AddRenderTarget(panel1);

            TM.Initialize(DX.Device, DX.Sprite);
            imageID = TM.LoadTexture("Assets/Graphics/ScA_WorldTileset.PNG", Color.Magenta);
            panel1.AutoScrollMinSize = new Size(TM.GetTextureWidth(imageID), TM.GetTextureHeight(imageID));
            TileSet.Width = TM.GetTextureWidth(imageID) / TileSize.Width;
            TileSet.Height = TM.GetTextureHeight(imageID) / TileSize.Height;

            currMap.TheWorld = new List<myLayers>();
            tempLayer.MyTiles = new Point[MapSize.Width, MapSize.Height];

            currMap.TheWorld.Add(tempLayer);

            TotalLayers = currMap.TheWorld.Count;

            nudTileHeight.Value = TileSize.Height;
            nudTileWidth.Value = TileSize.Width;
            nudLayer.Value = TotalLayers;

            nudMapHeight.Value = MapSize.Height;
            nudMapWidth.Value = MapSize.Width;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            isLooping = false;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            int nTempX = (e.X - panel1.AutoScrollPosition.X) / TileSize.Width;
            int nTempY = ((e.Y - panel1.AutoScrollPosition.Y) / TileSize.Height);
            tileSelected = new Point(nTempX, nTempY);
        }

        private void loadTilesetToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void panel2_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height)
            {
                Point Temp = new Point((e.X - panel2.AutoScrollPosition.X) / TileSize.Width, (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);
                currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[Temp.X, Temp.Y] = tileSelected;
            }
        }

        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {
            MouseLoc.Width = (e.X - panel2.AutoScrollPosition.X) / TileSize.Width;
            MouseLoc.Height = (e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height;
            if (mouseDown)
            {
                if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height)
                {
                    int nTempX = (e.X - panel2.AutoScrollPosition.X) / TileSize.Width;
                    int nTempY = ((e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height);

                    if (nTempX >= 0 && nTempY >= 0 && nTempX < MapSize.Width && nTempY < MapSize.Height)
                        currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[nTempX, nTempY] = tileSelected;
                }
            }
        }

        private void button1_MouseClick(object sender, MouseEventArgs e)
        {
            ShowGrid = !ShowGrid;
        }

        private void panel2_MouseUp(object sender, MouseEventArgs e)
        {
            mouseDown = false;
        }

        private void panel2_MouseDown(object sender, MouseEventArgs e)
        {
            mouseDown = true;
        }

        private void panel1_Scroll(object sender, ScrollEventArgs e)
        {
            DX.Clear(panel1, Color.Black);
            DX.DeviceBegin();
            DX.SpriteBegin();

            TM.Draw(imageID, panel1.AutoScrollPosition.X, panel1.AutoScrollPosition.Y);

            if (ShowGrid)
            {
                for (int i = 0; i < (TileSet.Width * TileSet.Height); i++)
                {
                    DX.DrawHollowRect(new Rectangle((i % TileSet.Width) * TileSize.Width + panel1.AutoScrollPosition.X, (i / TileSet.Height) * TileSize.Height + panel1.AutoScrollPosition.Y, TileSize.Width, TileSize.Height), Color.White, 1);
                }
            }

            /*
             Draw the Tileset here
            */

            DX.SpriteEnd();
            DX.DeviceEnd();
            DX.Present();
        }

    }
}
