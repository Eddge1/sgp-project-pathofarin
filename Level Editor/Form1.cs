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

        int imageID = -1;
        int tileSelected = 0;
        int TotalTiles = 25;
        int TotalLayers = 1;

        struct myLayers
        {
            List<int> myTiles;

            public List<int> MyTiles
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
            if (nudTileWidth.Value < 1)
                nudTileWidth.Value = 1;
            if (nudTileHeight.Value < 1)
                nudTileHeight.Value = 1;

            if (nudTileWidth.Value == 1 && nudTileHeight.Value == 1)
                nudTileHeight.Value = 8;
            TileSize.Width = Convert.ToInt32(nudTileWidth.Value);
            TileSize.Height = Convert.ToInt32(nudTileHeight.Value);
            
            TileSet.Width = TM.GetTextureWidth(imageID) / TileSize.Width;
            TileSet.Height = TM.GetTextureHeight(imageID) / TileSize.Height;

            if (nudLayer.Value < 1)
                nudLayer.Value = 1;

            if (nudLayer.Value > TotalLayers)
            {
                tempLayer.MyTiles = new List<int>();
                for (int i = 0; i < TotalTiles; i++)
                    tempLayer.MyTiles.Add(0);

                currMap.TheWorld.Add(tempLayer);
                TotalLayers = currMap.TheWorld.Count;
            }

        }

        public void Render()
        {
            DX.Clear(panel2, Color.Magenta);
            DX.DeviceBegin();
            DX.SpriteBegin();

            for (int nLayer = 0; nLayer < nudLayer.Value; nLayer++)
            {
                for (int i = 0; i < TotalTiles; i++)
                {
                    TM.Draw(imageID, (i % MapSize.Width) * TileSize.Width, (i / MapSize.Height) * TileSize.Height, 1, 1, new Rectangle(((currMap.TheWorld[nLayer].MyTiles[i] % TileSet.Width) * TileSize.Width), ((currMap.TheWorld[nLayer].MyTiles[i] / TileSet.Width) * TileSize.Height), TileSize.Width, TileSize.Height), 0, 0, 0);
                }
            }

            TM.Draw(imageID, MouseLoc.Width * TileSize.Width, MouseLoc.Height * TileSize.Height, 1, 1, new Rectangle(((tileSelected % TileSet.Width) * TileSize.Width), ((tileSelected / TileSet.Width) * TileSize.Height), TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(127, 255, 255, 255));

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

            DX.Clear(panel3, Color.Black);
            DX.DeviceBegin();
            DX.SpriteBegin();

            TM.Draw(imageID, 0, 0, (panel3.Size.Width / TileSize.Width), (panel3.Size.Height / TileSize.Height), new Rectangle(((tileSelected % TileSet.Width) * TileSize.Width), ((tileSelected / TileSet.Width) * TileSize.Height), TileSize.Width, TileSize.Height), 0, 0, 0, Color.FromArgb(255, 255, 255, 255));

            DX.SpriteEnd();
            DX.DeviceEnd();
            DX.Present();

        }

        public void Initialize()
        {
            DX.Initialize(panel2, false);
            DX.AddRenderTarget(panel1);
            DX.AddRenderTarget(panel3);

            TM.Initialize(DX.Device, DX.Sprite);
            imageID = TM.LoadTexture("Assets/Graphics/ScA_WorldTileset.PNG", Color.Magenta);
            panel1.AutoScrollMinSize = new Size(TM.GetTextureWidth(imageID), TM.GetTextureHeight(imageID));
            TileSet.Width = TM.GetTextureWidth(imageID) / TileSize.Width;
            TileSet.Height = TM.GetTextureHeight(imageID) / TileSize.Height;

            currMap.TheWorld = new List<myLayers>();
            tempLayer.MyTiles = new List<int>();

            for (int i = 0; i < TotalTiles; i++)
                tempLayer.MyTiles.Add(0);

            currMap.TheWorld.Add(tempLayer);

            TotalLayers = currMap.TheWorld.Count;

            nudTileHeight.Value = TileSize.Height;
            nudTileWidth.Value = TileSize.Width;
            nudLayer.Value = TotalLayers;
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
            tileSelected = ((e.Y - panel1.AutoScrollPosition.Y) / TileSize.Height) * TileSet.Width + ((e.X - panel1.AutoScrollPosition.X) / TileSize.Width);
        }

        private void loadTilesetToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void panel2_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.X < MapSize.Width * TileSize.Width && e.Y < MapSize.Height * TileSize.Height)
            {
                int nTemp = ((e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height) * MapSize.Width + ((e.X - panel2.AutoScrollPosition.X) / TileSize.Width);
                if (nTemp >= 0 && nTemp < TotalTiles)
                    currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[nTemp] = tileSelected;
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
                    int nTemp = ((e.Y - panel2.AutoScrollPosition.Y) / TileSize.Height) * MapSize.Width + ((e.X - panel2.AutoScrollPosition.X) / TileSize.Width);
                    if (nTemp >= 0 && nTemp < TotalTiles)
                        currMap.TheWorld[Convert.ToInt32(nudLayer.Value) - 1].MyTiles[nTemp] = tileSelected;
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
