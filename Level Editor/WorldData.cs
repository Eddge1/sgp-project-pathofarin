using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SGP_PoA_LevelEditor
{
    struct myTile
    {
        int x;
        int y;
        string szEventType;
        int warpX;
        int warpY;
        string szSpecial;
        myNPC npc;

        internal myNPC Npc
        {
            get { return npc; }
            set { npc = value; }
        }

        public int WarpY
        {
            get { return warpY; }
            set { warpY = value; }
        }

        public int WarpX
        {
            get { return warpX; }
            set { warpX = value; }
        }

        public string EventType
        {
            get { return szEventType; }
            set { szEventType = value; }
        }

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

        public string SzSpecial
        {
            get { return szSpecial; }
            set { szSpecial = value; }
        }

    }

    struct myLayers
    {
        myTile[,] myTiles;
        Size layerSize;
        Size offSet;

        public Size OffSet
        {
            get { return offSet; }
            set { offSet = value; }
        }

        public Size LayerSize
        {
            get { return layerSize; }
            set { layerSize = value; }
        }

        public myTile[,] MyTiles
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
}
