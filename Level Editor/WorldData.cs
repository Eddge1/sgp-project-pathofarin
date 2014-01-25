using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SGP_PoA_LevelEditor
{
    struct myTile
    {
        int x;
        int y;
        bool isBlocked;
        bool isEvent;
        bool isNPC;
        bool isWarp;
        int warpX;
        int warpY;
        string szSpecial;

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

        public bool IsWarp
        {
            get { return isWarp; }
            set { isWarp = value; }
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
        myTile[,] myTiles;

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
