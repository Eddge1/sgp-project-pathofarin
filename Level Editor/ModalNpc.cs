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

namespace SGP_PoA_LevelEditor
{
    public partial class ModalNpc : Form
    {
        myNPC tempNPC;
        myUnits tempUnit;
        myConvo tempConvo;

        public ModalNpc()
        {
            InitializeComponent();
            foreach (string szMapID in Directory.GetFiles(Environment.CurrentDirectory + "\\..\\Assets\\Data\\NPCS\\", "*.xml"))
            {
                tempNPC = new myNPC();
                tempNPC.MyConvos = new List<myConvo>();
                tempNPC.Units = new List<myUnits>();

                XElement xRoot = XElement.Load(szMapID);

                XAttribute xTotalConvo = xRoot.Attribute("Total_Conversations");
                XAttribute xName = xRoot.Attribute("Name");
                XAttribute xHostile = xRoot.Attribute("Hostile");
                XAttribute xTotalUnits = xRoot.Attribute("Units");
                IEnumerable<XElement> xConvos = xRoot.Elements("Convo");

                tempNPC.Name = xName.Value;
                tempNPC.IsHostile = Convert.ToBoolean(xHostile.Value);

                foreach (XElement convo in xConvos)
                {
                    myConvo temporary = new myConvo();
                    XAttribute xText = convo.Attribute("Text");
                    XAttribute xEventID = convo.Attribute("Event");

                    temporary.SzConvos = xText.Value;
                    temporary.SzEvent = xEventID.Value;

                    tempNPC.MyConvos.Add(temporary);
                }

                IEnumerable<XElement> xUnits = xRoot.Elements("Unit");

                foreach (XElement unit in xUnits)
                {
                    XAttribute xUnitName = unit.Attribute("Name");
                    myUnits temporary = new myUnits();

                    temporary.Name = xUnitName.Value;
                    tempNPC.Units.Add(temporary);
                }
                string szFileName = Path.GetFileName(szMapID);
                string szTemp = szFileName.Remove(szFileName.Length - 4, 4);
                lstNPC.Items.Add(tempNPC);
            }


            foreach (string szMapID in Directory.GetFiles(Environment.CurrentDirectory + "\\..\\Assets\\Data\\Units\\", "*.xml"))
            {
                tempUnit = new myUnits();
                tempUnit.DropChance = new List<decimal>();
                tempUnit.SzItems = new List<string>();

                XElement xRoot = XElement.Load(szMapID);
                XAttribute xHealth = xRoot.Attribute("Health");
                XAttribute xAp = xRoot.Attribute("Ap");
                XAttribute xAttack = xRoot.Attribute("Attack");
                XAttribute xExp = xRoot.Attribute("Exp");
                XAttribute xSpeed = xRoot.Attribute("Speed");
                XAttribute xLevel = xRoot.Attribute("Level");
                XAttribute xName = xRoot.Attribute("Name");
                XAttribute xAi = xRoot.Attribute("AI");
                XAttribute xItems = xRoot.Attribute("Total_Items");

                tempUnit.Name = xName.Value;
                tempUnit.Ai = xAi.Value;
                tempUnit.Hp = Convert.ToInt32(xHealth.Value);
                tempUnit.Ap = Convert.ToInt32(xAp.Value);
                tempUnit.Speed = Convert.ToInt32(xSpeed.Value);
                tempUnit.Exp = Convert.ToInt32(xExp.Value);
                tempUnit.Attack = Convert.ToInt32(xAttack.Value);
                tempUnit.Level = Convert.ToInt32(xLevel.Value);

                IEnumerable<XElement> xItemsDrop = xRoot.Elements("Item");

                foreach (XElement item in xItemsDrop)
                {
                    XAttribute xItemName = item.Attribute("Name");
                    XAttribute xDropChance = item.Attribute("Chance");

                    tempUnit.DropChance.Add(Convert.ToDecimal(xDropChance.Value));
                    tempUnit.SzItems.Add(xItemName.Value);
                }
                string szFileName = Path.GetFileName(szMapID);
                string szTemp = szFileName.Remove(szFileName.Length - 4, 4);
                lstUnitSelection.Items.Add(tempUnit);
            }
            cmb_AI.Items.Add("Brute");
            cmb_AI.Items.Add("BasicHealer");
            cmb_AI.Items.Add("OrcLeader");
            cmb_AI.Items.Add("TigerLily");
            cmb_AI.Items.Add("Valrion");

            cmb_Items.Items.Add("Potion");
            cmb_Items.Items.Add("Hi-Potion");
            cmb_Items.Items.Add("Titan-Potion");
            cmb_Items.Items.Add("Ether");
            cmb_Items.Items.Add("Hi-Ether");
            cmb_Items.Items.Add("Titan-Ether");

            cmb_AI.SelectedIndex = 0;
            cmb_Items.SelectedIndex = 0;

            tempNPC = new myNPC();
        }


        private void lstNPC_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstNPC.SelectedIndex >= 0)
            {
                lstUnitSelection.SelectedIndex = -1;
                grpUnits.Visible = false;
                groupBox1.Visible = true;

                lstConversation.Items.Clear();
                tempNPC = (myNPC)lstNPC.Items[lstNPC.SelectedIndex];
                for (int i = 0; i < tempNPC.MyConvos.Count; i++)
                    lstConversation.Items.Add(tempNPC.MyConvos[i]);

                checkBox1.Checked = tempNPC.IsHostile;
                tempUnit = new myUnits();
                for (int i = 0; i < tempNPC.Units.Count && i < 3; i++)
                {
                    tempUnit = tempNPC.Units[i];
                    lstAddUnit.Items.Add(tempUnit);
                }
                txtName.Text = tempNPC.Name;

            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            grpUnitList.Visible = checkBox1.Checked;
            if (checkBox1.Checked)
            {
                lstUnits.Items.Clear();
                for (int i = 0; i < lstUnitSelection.Items.Count; i++)
                {
                    lstUnits.Items.Add(lstUnitSelection.Items[i]);
                }
            }
            else
            {
                lstAddUnit.Items.Clear();
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (lstAddUnit.Items.Count < 3)
            {
                if (lstUnits.SelectedIndex >= 0)
                    lstAddUnit.Items.Add(lstUnits.Items[lstUnits.SelectedIndex]);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (lstAddUnit.SelectedIndex >= 0)
            {
                lstAddUnit.Items.RemoveAt(lstAddUnit.SelectedIndex);
                lstAddUnit.SelectedIndex = -1;
            }
        }

        private void btnConvoAdd_Click(object sender, EventArgs e)
        {
            tempConvo = new myConvo();
            tempConvo.SzConvos = txtConvo.Text;
            tempConvo.SzEvent = txtEvent.Text;

            txtConvo.Text = "";
            txtEvent.Text = "";
            lstConversation.Items.Add(tempConvo);


        }

        private void btnAdd_Click(object sender, EventArgs e)
        {

            tempNPC = new myNPC();
            tempNPC.MyConvos = new List<myConvo>();
            tempNPC.Units = new List<myUnits>();

            for (int i = 0; i < lstConversation.Items.Count; i++)
            {
                tempConvo = (myConvo)lstConversation.Items[i];
                tempNPC.MyConvos.Add(tempConvo);
            }
            tempNPC.IsHostile = checkBox1.Checked;
            tempUnit = new myUnits();
            for (int i = 0; i < lstAddUnit.Items.Count && i < 3; i++)
            {
                tempUnit = (myUnits)lstAddUnit.Items[i];
                tempNPC.Units.Add(tempUnit);
            }
            tempNPC.Name = txtName.Text;
            lstNPC.Items.Add(tempNPC);

            txtConvo.Text = "";
            txtEvent.Text = "";
            txtName.Text = "";
            checkBox1.Checked = false;
            lstConversation.Items.Clear();
            lstAddUnit.Items.Clear();

        }

        private void dtnDel_Click(object sender, EventArgs e)
        {
            if (lstNPC.SelectedIndex >= 0)
            {
                lstNPC.Items.RemoveAt(lstNPC.SelectedIndex);
                lstNPC.SelectedIndex = -1;
            }
        }

        private void btnConvoDel_Click(object sender, EventArgs e)
        {
            if (lstConversation.SelectedIndex >= 0)
            {
                lstConversation.Items.RemoveAt(lstConversation.SelectedIndex);
                lstConversation.SelectedIndex = -1;
            }
        }

        private void lstConversation_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstConversation.SelectedIndex >= 0)
            {
                tempConvo = (myConvo)lstConversation.Items[lstConversation.SelectedIndex];
                txtConvo.Text = tempConvo.SzConvos;
                txtEvent.Text = tempConvo.SzEvent;
            }
        }

        private void btnDone_Click(object sender, EventArgs e)
        {

            myNPC npc;
            myUnits unit;
            for (int i = 0; i < lstNPC.Items.Count; i++)
            {
                npc = (myNPC)lstNPC.Items[i];
                XElement xRoot = new XElement("NPC");
                XAttribute xTotalConvo = new XAttribute("Total_Conversations", npc.MyConvos.Count);
                XAttribute xName = new XAttribute("Name", npc.Name);
                XAttribute xHostile = new XAttribute("Hostile", npc.IsHostile);
                XAttribute xTotalUnits = new XAttribute("Units", npc.Units.Count);

                xRoot.Add(xTotalConvo);
                xRoot.Add(xName);
                xRoot.Add(xHostile);
                xRoot.Add(xTotalUnits);

                foreach (myConvo mc in npc.MyConvos)
                {
                    XElement xConversationID = new XElement("Convo");
                    XAttribute xText = new XAttribute("Text", mc.SzConvos);
                    XAttribute xEventID = new XAttribute("Event", mc.SzEvent);

                    xConversationID.Add(xText);
                    xConversationID.Add(xEventID);
                    xRoot.Add(xConversationID);
                }

                if (npc.IsHostile)
                {
                    foreach (myUnits mu in npc.Units)
                    {
                        XElement xUnit = new XElement("Unit");
                        XAttribute xUnitName = new XAttribute("Name", mu.Name);

                        xUnit.Add(xUnitName);
                        xRoot.Add(xUnit);
                    }
                }
                string temp = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\Assets\\Data\\NPCS\\" + npc.Name + ".xml");
                xRoot.Save(temp);

            }

            for (int i = 0; i < lstUnitSelection.Items.Count; i++)
            {
                unit = (myUnits)lstUnitSelection.Items[i];
                XElement xRoot = new XElement("Unit");
                XAttribute xHealth = new XAttribute("Health", unit.Hp);
                XAttribute xAp = new XAttribute("Ap", unit.Ap);
                XAttribute xAttack = new XAttribute("Attack", unit.Attack);
                XAttribute xExp = new XAttribute("Exp", unit.Exp);
                XAttribute xSpeed = new XAttribute("Speed", unit.Speed);
                XAttribute xLevel = new XAttribute("Level", unit.Level);
                XAttribute xName = new XAttribute("Name", unit.Name);
                XAttribute xAi = new XAttribute("AI", unit.Ai);
                XAttribute xItems = new XAttribute("Total_Items", unit.SzItems.Count);

                xRoot.Add(xName);
                xRoot.Add(xHealth);
                xRoot.Add(xAp);
                xRoot.Add(xAttack);
                xRoot.Add(xExp);
                xRoot.Add(xSpeed);
                xRoot.Add(xLevel);
                xRoot.Add(xAi);
                xRoot.Add(xItems);

                for (int j = 0; j < unit.SzItems.Count; j++)
                {
                    XElement xItemDrop = new XElement("Item");
                    XAttribute xItemName = new XAttribute("Name", unit.SzItems[j].ToString());
                    XAttribute xDropChance = new XAttribute("Chance", unit.DropChance[j]);

                    xItemDrop.Add(xItemName);
                    xItemDrop.Add(xDropChance);
                    xRoot.Add(xItemDrop);
                }
                string temp = Path.GetFullPath(Environment.CurrentDirectory + "\\..\\Assets\\Data\\Units\\" + unit.Name + ".xml");
                xRoot.Save(temp);
            }

        }

        private void btnRemoveItem_Click(object sender, EventArgs e)
        {
            if (lstItems.SelectedIndex >= 0)
            {
                tempUnit.SzItems.RemoveAt(lstItems.SelectedIndex);
                tempUnit.DropChance.RemoveAt(lstItems.SelectedIndex);
                lstItems.Items.RemoveAt(lstItems.SelectedIndex);
                lstItems.SelectedIndex = -1;
                nudDropChance.Value = 0;
            }
        }

        private void btnAddItem_Click(object sender, EventArgs e)
        {
            if (cmb_Items.SelectedIndex >= 0)
            {
                lstItems.Items.Add(cmb_Items.Items[cmb_Items.SelectedIndex].ToString());
                tempUnit.SzItems.Add(cmb_Items.Items[cmb_Items.SelectedIndex].ToString());
                tempUnit.DropChance.Add(nudDropChance.Value);
                cmb_Items.SelectedIndex = -1;
                nudDropChance.Value = 0;
            }
        }

        private void lstUnitAnimations_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void lstItems_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstItems.SelectedIndex >= 0)
            {
                for (int i = 0; i < cmb_Items.Items.Count; i++)
                {
                    if (cmb_Items.Items[i].ToString() == lstItems.Items[lstItems.SelectedIndex].ToString())
                    {
                        cmb_Items.SelectedIndex = i;
                        break;
                    }
                }

                nudDropChance.Value = tempUnit.DropChance[lstItems.SelectedIndex];
            }
        }

        private void nudDropChance_ValueChanged(object sender, EventArgs e)
        {

        }

        private void lstUnitSelection_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstUnitSelection.SelectedIndex >= 0)
            {
                lstNPC.SelectedIndex = -1;
                grpUnits.Visible = true;
                groupBox1.Visible = false;


                lstItems.Items.Clear();
                tempUnit = (myUnits)lstUnitSelection.Items[lstUnitSelection.SelectedIndex];
                for (int i = 0; i < tempUnit.SzItems.Count; i++)
                {
                    lstItems.Items.Add(tempUnit.SzItems[i].ToString());
                }

                nudAttack.Value = tempUnit.Attack;
                nudExperience.Value = tempUnit.Exp;
                nudHealth.Value = tempUnit.Hp;
                nudAP.Value = tempUnit.Ap;
                txtName.Text = tempUnit.Name;
                nudSpeed.Value = tempUnit.Speed;
                nudLevel.Value = tempUnit.Level;

                for (int i = 0; i < cmb_AI.Items.Count; i++)
                {
                    if (tempUnit.Ai == cmb_AI.Items[i].ToString())
                    {
                        cmb_AI.SelectedIndex = i;
                        break;
                    }
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            tempUnit.Ai = cmb_AI.Items[cmb_AI.SelectedIndex].ToString();
            tempUnit.Attack = Convert.ToInt32(nudAttack.Value);
            tempUnit.Exp = Convert.ToInt32(nudExperience.Value);
            tempUnit.Hp = Convert.ToInt32(nudHealth.Value);
            tempUnit.Ap = Convert.ToInt32(nudAP.Value);
            tempUnit.Speed = Convert.ToInt32(nudSpeed.Value);
            tempUnit.Level = Convert.ToInt32(nudLevel.Value);
            tempUnit.Name = txtUnitName.Text;

            lstUnitSelection.Items.Add(tempUnit);

            nudAttack.Value = 1;
            nudExperience.Value = 1;
            nudHealth.Value = 1;
            nudAP.Value = 1;
            nudSpeed.Value = 1;
            nudLevel.Value = 1;
            txtName.Text = "";
            cmb_AI.SelectedIndex = 0;
        }

        private void btnNewUnit_Click(object sender, EventArgs e)
        {
            lstNPC.SelectedIndex = -1;
            lstUnitSelection.SelectedIndex = -1;
            grpUnits.Visible = true;
            groupBox1.Visible = false;
            tempUnit = new myUnits();
            tempUnit.DropChance = new List<Decimal>();
            tempUnit.SzItems = new List<string>();
            lstItems.Items.Clear();
        }

        private void btnNewNPC_Click(object sender, EventArgs e)
        {
            lstNPC.SelectedIndex = -1;
            lstUnitSelection.SelectedIndex = -1;
            grpUnits.Visible = false;
            groupBox1.Visible = true;

            tempNPC = new myNPC();
            tempNPC.Units = new List<myUnits>();
            tempNPC.MyConvos = new List<myConvo>();
            lstConversation.Items.Clear();
            lstAddUnit.Items.Clear();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (lstUnitSelection.SelectedIndex >= 0)
            {
                lstUnitSelection.Items.RemoveAt(lstUnitSelection.SelectedIndex);
                lstUnitSelection.SelectedIndex = -1;
            }
        }


    }
}
