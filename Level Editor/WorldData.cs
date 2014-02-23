using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SGP_PoA_LevelEditor
{
    struct myChest
    {
        string szItem;
        decimal howMany;

        public string SzItem
        {
            get { return szItem; }
            set { szItem = value; }
        }

        public decimal HowMany
        {
            get { return howMany; }
            set { howMany = value; }
        }

        public override string ToString()
        {
            return SzItem + " x" + HowMany.ToString();
        }
    }

    struct myTile
    {
        int x;
        int y;
        string szEventType;
        string szBroadCast;
        string szErase;
        int warpX;
        int warpY;
        string szSpecial;
        List<myChest> cItems;
        List<Point> m_vWaypoints;

        public string BroadCast
        {
            get { return szBroadCast; }
            set { szBroadCast = value; }
        }

        public string SzErase
        {
            get { return szErase; }
            set { szErase = value; }
        }

        internal List<myChest> CItems
        {
            get { return cItems; }
            set { cItems = value; }
        }

        public List<Point> Waypoints
        {
            get { return m_vWaypoints; }
            set { m_vWaypoints = value; }
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
