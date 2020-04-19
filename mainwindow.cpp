#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("background_002.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::m_calculateBattleStats(void)
{
    m_attribute_str = m_attribute_str_base + m_attribute_str_norm + m_attribute_str_natg;
    m_attribute_con = m_attribute_con_base + m_attribute_con_norm + m_attribute_con_natg;
    m_attribute_dex = m_attribute_dex_base + m_attribute_dex_norm + m_attribute_dex_natg;
    m_attribute_int = m_attribute_int_base + m_attribute_int_norm + m_attribute_int_natg;
    m_attribute_spr = m_attribute_spr_base + m_attribute_spr_norm + m_attribute_spr_natg;
    m_attribute_wis = m_attribute_wis_base + m_attribute_wis_norm + m_attribute_wis_natg;

    if (m_attribute_str > 10)
    {
        m_battleStat_pa_norm = (m_physical_attack == eAttribute::aSTR) ? ((m_attribute_str - 10) / 2) : 0;
        m_battleStat_pd_norm = (m_physical_defense == eAttribute::aSTR) ? ((m_attribute_str - 10) / 2) : 0;
    }
    if (m_attribute_con > 10)
    {
        m_battleStat_pa_norm = (m_physical_attack == eAttribute::aCON) ? ((m_attribute_con - 10) / 2) : 0;
        m_battleStat_pd_norm = (m_physical_defense == eAttribute::aCON) ? ((m_attribute_con - 10) / 2) : 0;
        m_battleStat_hp_norm = (m_attribute_con - 10) / 2;
    }
    if (m_attribute_dex > 10)
    {
        m_battleStat_pa_norm = (m_physical_attack == eAttribute::aDEX) ? ((m_attribute_dex - 10) / 2) : 0;
        m_battleStat_pd_norm = (m_physical_defense == eAttribute::aDEX) ? ((m_attribute_dex - 10) / 2) : 0;
    }
    if (m_attribute_int > 10)
    {
        m_battleStat_pa_norm = (m_physical_attack == eAttribute::aINT) ? ((m_attribute_int - 10) / 2) : 0;
        m_battleStat_pd_norm = (m_physical_defense == eAttribute::aINT) ? ((m_attribute_int - 10) / 2) : 0;
        m_battleStat_ma_norm = (m_attribute_int - 10) / 2;
    }
    if (m_attribute_spr > 10)
    {
        m_battleStat_pa_norm = (m_physical_attack == eAttribute::aSPR) ? ((m_attribute_spr - 10) / 2) : 0;
        m_battleStat_pd_norm = (m_physical_defense == eAttribute::aSPR) ? ((m_attribute_spr - 10) / 2) : 0;
        m_battleStat_mp_norm = (m_attribute_spr - 10) / 2;
        m_battleStat_md_norm = (m_attribute_spr - 10) / 2;
    }
    if (m_attribute_wis > 10)
    {
        m_battleStat_pa_norm = (m_physical_attack == eAttribute::aWIS) ? ((m_attribute_wis - 10) / 2) : 0;
        m_battleStat_pd_norm = (m_physical_defense == eAttribute::aWIS) ? ((m_attribute_wis - 10) / 2) : 0;
    }

    m_battleStat_hp = m_battleStat_hp_base + m_battleStat_hp_norm + m_battleStat_hp_gear;
    m_battleStat_mp = m_battleStat_mp_base + m_battleStat_mp_norm + m_battleStat_mp_gear;
    m_battleStat_pa = m_battleStat_pa_base + m_battleStat_pa_norm + m_battleStat_pa_gear;
    m_battleStat_ma = m_battleStat_ma_base + m_battleStat_ma_norm + m_battleStat_ma_gear;
    m_battleStat_pd = m_battleStat_pd_base + m_battleStat_pd_norm + m_battleStat_pd_gear;
    m_battleStat_md = m_battleStat_md_base + m_battleStat_md_norm + m_battleStat_md_gear;

    ui->label_health_points_var->setText(std::to_string(m_battleStat_hp).c_str());
    ui->label_mana_points_var->setText(std::to_string(m_battleStat_mp).c_str());
    ui->label_physical_attack_var->setText(std::to_string(m_battleStat_pa).c_str());
    ui->label_magical_attack_var->setText(std::to_string(m_battleStat_ma).c_str());
    ui->label_physical_defence_var->setText(std::to_string(m_battleStat_pd).c_str());
    ui->label_magical_defence_var->setText(std::to_string(m_battleStat_md).c_str());
}

void MainWindow::m_calculate(void)
{
    m_gold = 252;
    m_attribute_points = 24;
    m_skill_points  = m_secluded_training ? 7 : 0;
    m_battleStat_hp      = 0;
    m_battleStat_hp_base = 20;
    m_battleStat_hp_norm = 0;
    m_battleStat_mp_gear = 0;
    m_battleStat_mp      = 0;
    m_battleStat_mp_base = 20;
    m_battleStat_mp_norm = 0;
    m_battleStat_mp_gear = 0;
    m_battleStat_pa      = 0;
    m_battleStat_pa_base = 0;
    m_battleStat_pa_norm = 0;
    m_battleStat_pa_gear = 0;
    m_battleStat_ma      = 0;
    m_battleStat_ma_base = 0;
    m_battleStat_ma_norm = 0;
    m_battleStat_ma_gear = 0;
    m_battleStat_pd      = 0;
    m_battleStat_pd_base = 10;
    m_battleStat_pd_norm = 0;
    m_battleStat_pd_gear = 0;
    m_battleStat_md      = 0;
    m_battleStat_md_base = 10;
    m_battleStat_md_norm = 0;
    m_battleStat_md_gear = 0;

    m_attribute_str      = 0;
    m_attribute_str_base = ((m_natural_genius) && (m_natural_genius_a1 == eAttribute::aSTR)) ? 14 : 8;
    m_attribute_str_norm = 0;
    m_attribute_str_natg = 0;
    m_attribute_con      = 0;
    m_attribute_con_base = ((m_natural_genius) && (m_natural_genius_a1 == eAttribute::aCON)) ? 14 : 8;
    m_attribute_con_norm = 0;
    m_attribute_con_natg = 0;
    m_attribute_dex      = 0;
    m_attribute_dex_base = ((m_natural_genius) && (m_natural_genius_a1 == eAttribute::aDEX)) ? 14 : 8;
    m_attribute_dex_norm = 0;
    m_attribute_dex_natg = 0;
    m_attribute_int      = 0;
    m_attribute_int_base = ((m_natural_genius) && (m_natural_genius_a1 == eAttribute::aINT)) ? 14 : 8;
    m_attribute_int_norm = 0;
    m_attribute_int_natg = 0;
    m_attribute_spr      = 0;
    m_attribute_spr_base = ((m_natural_genius) && (m_natural_genius_a1 == eAttribute::aSPR)) ? 14 : 8;
    m_attribute_spr_norm = 0;
    m_attribute_spr_natg = 0;
    m_attribute_wis      = 0;
    m_attribute_wis_base = ((m_natural_genius) && (m_natural_genius_a1 == eAttribute::aWIS)) ? 14 : 8;
    m_attribute_wis_norm = 0;
    m_attribute_wis_natg = 0;

    for (uint32_t i = 1; i < m_level+1; i++)
    {
        uint32_t mLevel = i % 5;

        // Battle stat even level bonuses
        if ((i > 1) && ((i % 2) == 0))
        {
            m_battleStat_hp_base += 1;
            m_battleStat_mp_base += 1;
            m_battleStat_pa_base += 1;
            m_battleStat_ma_base += 1;
            m_battleStat_pd_base += 1;
            m_battleStat_md_base += 1;
        }

        // Class bonuses
        if (i > 1)
        {
            if (m_class == eClass::archer)
            {
                m_battleStat_hp_base    += 2;
                m_battleStat_mp_base    += 2;
            }
            else if (m_class == eClass::mage)
            {
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 3;
            }
            else if (m_class == eClass::fighter)
            {
                m_battleStat_hp_base    += 3;
                m_battleStat_mp_base    += 1;
            }
        }

        // Balance Curve
        if (m_growthCurve == eGrowthCurve::balanceCurve)
        {
            if (mLevel == 1)
            {
                m_skill_points     += 3;
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
            }
            else if (mLevel == 2)
            {
                m_attribute_points += 2;
            }
            else if (mLevel == 3)
            {
                m_skill_points     += 2;
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
                m_attribute_points += 1;
            }
            else if (mLevel == 4)
            {
                m_attribute_str_base    += 1;
                m_attribute_con_base    += 1;
                m_attribute_dex_base    += 1;
                m_attribute_int_base    += 1;
                m_attribute_spr_base    += 1;
                m_attribute_wis_base    += 1;
            }
            else if (mLevel == 0) // 5
            {
                m_skill_points     += 3;
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
            }
        }

        // Resource Curve
        if (m_growthCurve == eGrowthCurve::resourceCurve)
        {
            if (mLevel == 1)
            {
                m_skill_points     += 1;
            }
            else if (mLevel == 2)
            {
                m_skill_points     += 1;
                m_attribute_points += 1;
                if (m_default_hp)
                {
                    m_battleStat_hp_base += 3;
                }
                else
                {
                    m_battleStat_mp_base += 3;
                }
            }
            else if (mLevel == 3)
            {
                m_skill_points     += 1;
                m_attribute_str_base    += 1;
                m_attribute_con_base    += 1;
                m_attribute_dex_base    += 1;
                m_attribute_int_base    += 1;
                m_attribute_spr_base    += 1;
                m_attribute_wis_base    += 1;
                if (m_default_hp)
                {
                    m_battleStat_mp_base += 2;
                }
                else
                {
                    m_battleStat_hp_base += 2;
                }
            }
            else if (mLevel == 4)
            {
                m_skill_points     += 1;
                m_attribute_points += 1;
                if (m_default_hp)
                {
                    m_battleStat_hp_base += 3;
                }
                else
                {
                    m_battleStat_mp_base += 3;
                }
            }
            else if (mLevel == 0) // 5
            {
                m_skill_points     += 2;
            }
        }

        // Skill Curve
        if (m_growthCurve == eGrowthCurve::skillCurve)
        {
            if (mLevel == 1)
            {
                m_attribute_points += 1;
            }
            else if (mLevel == 2)
            {
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
                m_attribute_str_base    += 1;
                m_attribute_con_base    += 1;
                m_attribute_dex_base    += 1;
                m_attribute_int_base    += 1;
                m_attribute_spr_base    += 1;
                m_attribute_wis_base    += 1;
            }
            else if (mLevel == 3)
            {
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
                m_attribute_points += 1;
            }
            else if (mLevel == 4)
            {
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
            }
            else if (mLevel == 0) // 5
            {
                m_skill_points     += 10;
            }
        }

        // Attribute Curve
        if (m_growthCurve == eGrowthCurve::attributeCurve)
        {
            if (mLevel == 1)
            {
                m_skill_points     += 1;
                m_attribute_points += 2;
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
            }
            else if (mLevel == 2)
            {
                m_skill_points     += 1;
            }
            else if (mLevel == 3)
            {
                m_skill_points     += 2;
                m_attribute_points += 1;
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
                m_attribute_str_base    += 1;
                m_attribute_con_base    += 1;
                m_attribute_dex_base    += 1;
                m_attribute_int_base    += 1;
                m_attribute_spr_base    += 1;
                m_attribute_wis_base    += 1;
            }
            else if (mLevel == 4)
            {
                m_skill_points     += 1;
            }
            else if (mLevel == 0) // 5
            {
                m_skill_points     += 1;
                m_attribute_points += 2;
                m_battleStat_hp_base    += 1;
                m_battleStat_mp_base    += 1;
            }
        }
    }

    if (m_level < 10)
        m_gold = m_gold_bracket[0] + m_gold_bracket[1];
    else if (m_level < 20)
        m_gold = m_gold_bracket[0] + m_gold_bracket[1] + m_gold_bracket[2];
    else if (m_level < 30)
        m_gold = m_gold_bracket[1] + m_gold_bracket[2] + m_gold_bracket[3];
    else if (m_level < 40)
        m_gold = m_gold_bracket[2] + m_gold_bracket[3] + m_gold_bracket[4];
    else if (m_level < 50)
        m_gold = m_gold_bracket[3] + m_gold_bracket[4] + m_gold_bracket[5];
    else if (m_level < 60)
        m_gold = m_gold_bracket[4] + m_gold_bracket[5] + m_gold_bracket[6];
    else if (m_level < 70)
        m_gold = m_gold_bracket[5] + m_gold_bracket[6] + m_gold_bracket[7];
    else if (m_level < 80)
        m_gold = m_gold_bracket[6] + m_gold_bracket[7] + m_gold_bracket[8];
    else if (m_level < 90)
        m_gold = m_gold_bracket[7] + m_gold_bracket[8] + m_gold_bracket[9];
    else if (m_level == 100)
        m_gold = m_gold_bracket[9] + m_gold_bracket[10];

    m_attribute_str = m_attribute_str_base + m_attribute_str_norm + m_attribute_str_natg;
    m_attribute_con = m_attribute_con_base + m_attribute_con_norm + m_attribute_con_natg;
    m_attribute_dex = m_attribute_dex_base + m_attribute_dex_norm + m_attribute_dex_natg;
    m_attribute_int = m_attribute_int_base + m_attribute_int_norm + m_attribute_int_natg;
    m_attribute_spr = m_attribute_spr_base + m_attribute_spr_norm + m_attribute_spr_natg;
    m_attribute_wis = m_attribute_wis_base + m_attribute_wis_norm + m_attribute_wis_natg;

    m_battleStat_hp = m_battleStat_hp_base + m_battleStat_hp_norm + m_battleStat_hp_gear;
    m_battleStat_mp = m_battleStat_mp_base + m_battleStat_mp_norm + m_battleStat_mp_gear;
    m_battleStat_pa = m_battleStat_pa_base + m_battleStat_pa_norm + m_battleStat_pa_gear;
    m_battleStat_ma = m_battleStat_ma_base + m_battleStat_ma_norm + m_battleStat_ma_gear;
    m_battleStat_pd = m_battleStat_pd_base + m_battleStat_pd_norm + m_battleStat_pd_gear;
    m_battleStat_md = m_battleStat_md_base + m_battleStat_md_norm + m_battleStat_md_gear;

    ui->label_gold_var->setText(std::to_string(m_gold).c_str());
    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_skill_points_var->setText(std::to_string(m_skill_points).c_str());

    ui->label_strength_var->setText(std::to_string(m_attribute_str).c_str());
    ui->label_constitution_var->setText(std::to_string(m_attribute_con).c_str());
    ui->label_dexterity_var->setText(std::to_string(m_attribute_dex).c_str());
    ui->label_intelligence_var->setText(std::to_string(m_attribute_int).c_str());
    ui->label_spirit_var->setText(std::to_string(m_attribute_spr).c_str());
    ui->label_wisdom_var->setText(std::to_string(m_attribute_wis).c_str());

    ui->label_health_points_var->setText(std::to_string(m_battleStat_hp).c_str());
    ui->label_mana_points_var->setText(std::to_string(m_battleStat_mp).c_str());
    ui->label_physical_attack_var->setText(std::to_string(m_battleStat_pa).c_str());
    ui->label_magical_attack_var->setText(std::to_string(m_battleStat_ma).c_str());
    ui->label_physical_defence_var->setText(std::to_string(m_battleStat_pd).c_str());
    ui->label_magical_defence_var->setText(std::to_string(m_battleStat_md).c_str());

    m_calculateBattleStats();
}

MainWindow::eAttribute MainWindow::intToAttribute(int _value)
{
    switch (_value)
    {
        case 0:
            return eAttribute::aSTR;
        case 1:
            return eAttribute::aCON;
        case 2:
            return eAttribute::aDEX;
        case 3:
            return eAttribute::aINT;
        case 4:
            return eAttribute::aSPR;
        case 5:
            return eAttribute::aWIS;
        case 6:
        default:
            return eAttribute::aSTR;
    }
}

int MainWindow::attributeToInt(MainWindow::eAttribute _attribute)
{
    switch (_attribute)
    {
        case eAttribute::aSTR:
            return 0;
        case eAttribute::aCON:
            return 1;
        case eAttribute::aDEX:
            return 2;
        case eAttribute::aINT:
            return 3;
        case eAttribute::aSPR:
            return 4;
        case eAttribute::aWIS:
            return 5;
        default:
            return 0;
    }
}

void MainWindow::on_checkBox_secluded_training_clicked()
{
    if (ui->checkBox_secluded_training->isChecked())
    {
        ui->checkBox_natural_genius->setChecked(false);
        ui->checkBox_secluded_training->setChecked(true);
        m_secluded_training  = true;
        m_skill_points += 7;
        m_natural_genius     = false;
        ui->comboBox_natural_genius_a1->setEnabled(false);
        ui->comboBox_natural_genius_a2->setEnabled(false);
        ui->comboBox_natural_genius_a3->setEnabled(false);
    }
    else
    {
        ui->checkBox_secluded_training->setChecked(false);
        m_secluded_training = false;
        m_skill_points -= 7;
    }
    ui->label_skill_points_var->setText(std::to_string(m_skill_points).c_str());
}

void MainWindow::on_checkBox_natural_genius_clicked()
{
    if (ui->checkBox_natural_genius->isChecked())
    {
        ui->checkBox_secluded_training->setChecked(false);
        ui->checkBox_natural_genius->setChecked(true);
        m_natural_genius     = true;
        ui->comboBox_natural_genius_a1->setEnabled(true);
        ui->comboBox_natural_genius_a2->setEnabled(true);
        ui->comboBox_natural_genius_a3->setEnabled(true);
        m_secluded_training = false;
    }
    else
    {
        ui->checkBox_natural_genius->setChecked(false);
        m_natural_genius     = false;
        ui->comboBox_natural_genius_a1->setEnabled(false);
        ui->comboBox_natural_genius_a2->setEnabled(false);
        ui->comboBox_natural_genius_a3->setEnabled(false);
    }
    m_calculate();
}

void MainWindow::on_comboBox_class_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
           m_class = eClass::archer;
        break;
        case 1:
           m_class = eClass::mage;
        break;
        case 2:
           m_class = eClass::fighter;
        break;
    }
    m_calculate();
}

void MainWindow::on_comboBox_growth_curve_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
           m_growthCurve = eGrowthCurve::balanceCurve;
           ui->comboBox_hp_mp->setEnabled(false);
        break;
        case 1:
            m_growthCurve = eGrowthCurve::resourceCurve;
            ui->comboBox_hp_mp->setEnabled(true);
        break;
        case 2:
            m_growthCurve = eGrowthCurve::skillCurve;
            ui->comboBox_hp_mp->setEnabled(false);
        break;
        case 3:
            m_growthCurve = eGrowthCurve::attributeCurve;
            ui->comboBox_hp_mp->setEnabled(false);
        break;
    }
    m_calculate();
}

void MainWindow::on_spinBox_level_valueChanged(int arg1)
{
    m_level = static_cast<uint32_t>(arg1);
    m_calculate();
}

void MainWindow::on_pushButton_strength_inc_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aSTR) || (m_natural_genius_a3 == eAttribute::aSTR)))
    {
        if (m_attribute_points > 1)
        {
            m_attribute_points -= 2;
            m_attribute_str_natg++;
        }
    }
    else
    {
        if (m_attribute_points > 0)
        {
            m_attribute_points--;
            m_attribute_str_norm++;
        }
    }

    m_attribute_str = m_attribute_str_base + m_attribute_str_norm + m_attribute_str_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_strength_var->setText(std::to_string(m_attribute_str).c_str());
}

void MainWindow::on_pushButton_strength_dec_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aSTR) || (m_natural_genius_a3 == eAttribute::aSTR)))
    {
        if (m_attribute_str_natg > 0)
        {
            m_attribute_points += 2;
            m_attribute_str_natg--;
        }
    }
    else
    {
        if (m_attribute_str_norm > 0)
        {
            m_attribute_points++;
            m_attribute_str_norm--;
        }
    }

    m_attribute_str = m_attribute_str_base + m_attribute_str_norm + m_attribute_str_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_strength_var->setText(std::to_string(m_attribute_str).c_str());
}

void MainWindow::on_pushButton_constitution_inc_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aCON) || (m_natural_genius_a3 == eAttribute::aCON)))
    {
        if (m_attribute_points > 1)
        {
            m_attribute_points -= 2;
            m_attribute_con_natg++;
        }
    }
    else
    {
        if (m_attribute_points > 0)
        {
            m_attribute_points--;
            m_attribute_con_norm++;
        }
    }

    m_attribute_con = m_attribute_con_base + m_attribute_con_norm + m_attribute_con_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_constitution_var->setText(std::to_string(m_attribute_con).c_str());
}

void MainWindow::on_pushButton_constitution_dec_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aCON) || (m_natural_genius_a3 == eAttribute::aCON)))
    {
        if (m_attribute_con_natg > 0)
        {
            m_attribute_points += 2;
            m_attribute_con_natg--;
        }
    }
    else
    {
        if (m_attribute_con_norm > 0)
        {
            m_attribute_points++;
            m_attribute_con_norm--;
        }
    }

    m_attribute_con = m_attribute_con_base + m_attribute_con_norm + m_attribute_con_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_constitution_var->setText(std::to_string(m_attribute_con).c_str());
}

void MainWindow::on_pushButton_dexterity_inc_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aDEX) || (m_natural_genius_a3 == eAttribute::aDEX)))
    {
        if (m_attribute_points > 1)
        {
            m_attribute_points -= 2;
            m_attribute_dex_natg++;
        }
    }
    else
    {
        if (m_attribute_points > 0)
        {
            m_attribute_points--;
            m_attribute_dex_norm++;
        }
    }

    m_attribute_dex = m_attribute_dex_base + m_attribute_dex_norm + m_attribute_dex_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_dexterity_var->setText(std::to_string(m_attribute_dex).c_str());
}

void MainWindow::on_pushButton_dexterity_dec_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aDEX) || (m_natural_genius_a3 == eAttribute::aDEX)))
    {
        if (m_attribute_dex_natg > 0)
        {
            m_attribute_points += 2;
            m_attribute_dex_natg--;
        }
    }
    else
    {
        if (m_attribute_dex_norm > 0)
        {
            m_attribute_points++;
            m_attribute_dex_norm--;
        }
    }

    m_attribute_dex = m_attribute_dex_base + m_attribute_dex_norm + m_attribute_dex_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_dexterity_var->setText(std::to_string(m_attribute_dex).c_str());
}

void MainWindow::on_pushButton_intelligence_inc_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aINT) || (m_natural_genius_a3 == eAttribute::aINT)))
    {
        if (m_attribute_points > 1)
        {
            m_attribute_points -= 2;
            m_attribute_int_natg++;
        }
    }
    else
    {
        if (m_attribute_points > 0)
        {
            m_attribute_points--;
            m_attribute_int_norm++;
        }
    }

    m_attribute_int = m_attribute_int_base + m_attribute_int_norm + m_attribute_int_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_intelligence_var->setText(std::to_string(m_attribute_int).c_str());
}

void MainWindow::on_pushButton_intelligence_dec_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aINT) || (m_natural_genius_a3 == eAttribute::aINT)))
    {
        if (m_attribute_int_natg > 0)
        {
            m_attribute_points += 2;
            m_attribute_int_natg--;
        }
    }
    else
    {
        if (m_attribute_int_norm > 0)
        {
            m_attribute_points++;
            m_attribute_int_norm--;
        }
    }

    m_attribute_int = m_attribute_int_base + m_attribute_int_norm + m_attribute_int_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_intelligence_var->setText(std::to_string(m_attribute_int).c_str());
}

void MainWindow::on_pushButton_spirit_inc_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aSPR) || (m_natural_genius_a3 == eAttribute::aSPR)))
    {
        if (m_attribute_points > 1)
        {
            m_attribute_points -= 2;
            m_attribute_spr_natg++;
        }
    }
    else
    {
        if (m_attribute_points > 0)
        {
            m_attribute_points--;
            m_attribute_spr_norm++;
        }
    }

    m_attribute_spr = m_attribute_spr_base + m_attribute_spr_norm + m_attribute_spr_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_spirit_var->setText(std::to_string(m_attribute_spr).c_str());
}

void MainWindow::on_pushButton_spirit_dec_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aSPR) || (m_natural_genius_a3 == eAttribute::aSPR)))
    {
        if (m_attribute_spr_natg > 0)
        {
            m_attribute_points += 2;
            m_attribute_spr_natg--;
        }
    }
    else
    {
        if (m_attribute_spr_norm > 0)
        {
            m_attribute_points++;
            m_attribute_spr_norm--;
        }
    }

    m_attribute_spr = m_attribute_spr_base + m_attribute_spr_norm + m_attribute_spr_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_spirit_var->setText(std::to_string(m_attribute_spr).c_str());
}

void MainWindow::on_pushButton_wisdom_inc_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aWIS) || (m_natural_genius_a3 == eAttribute::aWIS)))
    {
        if (m_attribute_points > 1)
        {
            m_attribute_points -= 2;
            m_attribute_wis_natg++;
        }
    }
    else
    {
        if (m_attribute_points > 0)
        {
            m_attribute_points--;
            m_attribute_wis_norm++;
        }
    }

    m_attribute_wis = m_attribute_wis_base + m_attribute_wis_norm + m_attribute_wis_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_wisdom_var->setText(std::to_string(m_attribute_wis).c_str());
}

void MainWindow::on_pushButton_wisdom_dec_clicked()
{
    if ((m_natural_genius) && ((m_natural_genius_a2 == eAttribute::aWIS) || (m_natural_genius_a3 == eAttribute::aWIS)))
    {
        if (m_attribute_wis_natg > 0)
        {
            m_attribute_points += 2;
            m_attribute_wis_natg--;
        }
    }
    else
    {
        if (m_attribute_wis_norm > 0)
        {
            m_attribute_points++;
            m_attribute_wis_norm--;
        }
    }

    m_attribute_wis = m_attribute_wis_base + m_attribute_wis_norm + m_attribute_wis_natg;
    m_calculateBattleStats();

    ui->label_character_attribute_points->setText(std::to_string(m_attribute_points).c_str());
    ui->label_wisdom_var->setText(std::to_string(m_attribute_wis).c_str());
}

void MainWindow::on_comboBox_natural_genius_a1_currentIndexChanged(int index)
{
    const bool blocked_a1 = ui->comboBox_natural_genius_a1->signalsBlocked();
    ui->comboBox_natural_genius_a1->blockSignals(true);
    const bool blocked_a2 = ui->comboBox_natural_genius_a2->signalsBlocked();
    ui->comboBox_natural_genius_a2->blockSignals(true);
    const bool blocked_a3 = ui->comboBox_natural_genius_a3->signalsBlocked();
    ui->comboBox_natural_genius_a3->blockSignals(true);

    m_natural_genius_a1 = intToAttribute(index);

    m_attribute_str_natg = (m_natural_genius_a1 == eAttribute::aSTR) ? 6 : 0;
    m_attribute_con_natg = (m_natural_genius_a1 == eAttribute::aCON) ? 6 : 0;
    m_attribute_dex_natg = (m_natural_genius_a1 == eAttribute::aDEX) ? 6 : 0;
    m_attribute_int_natg = (m_natural_genius_a1 == eAttribute::aINT) ? 6 : 0;
    m_attribute_spr_natg = (m_natural_genius_a1 == eAttribute::aSPR) ? 6 : 0;
    m_attribute_wis_natg = (m_natural_genius_a1 == eAttribute::aWIS) ? 6 : 0;

    if (m_natural_genius_a1 == m_natural_genius_a2)
    {
        for (uint32_t i = 0; i < m_numAttributes; i++)
        {
            if ((i != m_natural_genius_a1) && (i != m_natural_genius_a3))
            {
                m_natural_genius_a2 = intToAttribute(static_cast<int>(i));
                ui->comboBox_natural_genius_a2->setCurrentIndex(attributeToInt(m_natural_genius_a2));
                break;
            }
        }
    }
    if (m_natural_genius_a1 == m_natural_genius_a3)
    {
        for (uint32_t i = 0; i < m_numAttributes; i++)
        {
            if ((i != m_natural_genius_a1) && (i != m_natural_genius_a2))
            {
                m_natural_genius_a3 = intToAttribute(static_cast<int>(i));
                ui->comboBox_natural_genius_a3->setCurrentIndex(attributeToInt(m_natural_genius_a3));
                break;
            }
        }
    }

    ui->comboBox_natural_genius_a1->blockSignals(blocked_a1);
    ui->comboBox_natural_genius_a2->blockSignals(blocked_a2);
    ui->comboBox_natural_genius_a3->blockSignals(blocked_a3);
    m_calculateBattleStats();
}

void MainWindow::on_comboBox_natural_genius_a2_currentIndexChanged(int index)
{
    const bool blocked_a1 = ui->comboBox_natural_genius_a1->signalsBlocked();
    ui->comboBox_natural_genius_a1->blockSignals(true);
    const bool blocked_a2 = ui->comboBox_natural_genius_a2->signalsBlocked();
    ui->comboBox_natural_genius_a2->blockSignals(true);
    const bool blocked_a3 = ui->comboBox_natural_genius_a3->signalsBlocked();
    ui->comboBox_natural_genius_a3->blockSignals(true);

    m_natural_genius_a2 = intToAttribute(index);
    if (m_natural_genius_a2 == m_natural_genius_a1)
    {
        for (uint32_t i = 0; i < m_numAttributes; i++)
        {
            if ((i != m_natural_genius_a2) && (i != m_natural_genius_a3))
            {
                m_natural_genius_a1 = intToAttribute(static_cast<int>(i));
                m_attribute_str_natg = (m_natural_genius_a1 == eAttribute::aSTR) ? 6 : 0;
                m_attribute_con_natg = (m_natural_genius_a1 == eAttribute::aCON) ? 6 : 0;
                m_attribute_dex_natg = (m_natural_genius_a1 == eAttribute::aDEX) ? 6 : 0;
                m_attribute_int_natg = (m_natural_genius_a1 == eAttribute::aINT) ? 6 : 0;
                m_attribute_spr_natg = (m_natural_genius_a1 == eAttribute::aSPR) ? 6 : 0;
                m_attribute_wis_natg = (m_natural_genius_a1 == eAttribute::aWIS) ? 6 : 0;
                ui->comboBox_natural_genius_a1->setCurrentIndex(static_cast<int>(m_natural_genius_a1));
                break;
            }
        }
    }
    if (m_natural_genius_a2 == m_natural_genius_a3)
    {
        for (uint32_t i = 0; i < m_numAttributes; i++)
        {
            if ((i != m_natural_genius_a2) && (i != m_natural_genius_a1))
            {
                m_natural_genius_a3 = intToAttribute(static_cast<int>(i));
                ui->comboBox_natural_genius_a3->setCurrentIndex(static_cast<int>(m_natural_genius_a3));
                break;
            }
        }
    }
    ui->comboBox_natural_genius_a1->blockSignals(blocked_a1);
    ui->comboBox_natural_genius_a2->blockSignals(blocked_a2);
    ui->comboBox_natural_genius_a3->blockSignals(blocked_a3);
    m_calculateBattleStats();
}

void MainWindow::on_comboBox_natural_genius_a3_currentIndexChanged(int index)
{
    const bool blocked_a1 = ui->comboBox_natural_genius_a1->signalsBlocked();
    ui->comboBox_natural_genius_a1->blockSignals(true);
    const bool blocked_a2 = ui->comboBox_natural_genius_a2->signalsBlocked();
    ui->comboBox_natural_genius_a2->blockSignals(true);
    const bool blocked_a3 = ui->comboBox_natural_genius_a3->signalsBlocked();
    ui->comboBox_natural_genius_a3->blockSignals(true);

    m_natural_genius_a3 = intToAttribute(index);
    if (m_natural_genius_a3 == m_natural_genius_a1)
    {
        for (uint32_t i = 0; i < m_numAttributes; i++)
        {
            if ((i != m_natural_genius_a3) && (i != m_natural_genius_a2))
            {
                m_natural_genius_a1 = intToAttribute(static_cast<int>(i));
                m_attribute_str_natg = (m_natural_genius_a1 == eAttribute::aSTR) ? 6 : 0;
                m_attribute_con_natg = (m_natural_genius_a1 == eAttribute::aCON) ? 6 : 0;
                m_attribute_dex_natg = (m_natural_genius_a1 == eAttribute::aDEX) ? 6 : 0;
                m_attribute_int_natg = (m_natural_genius_a1 == eAttribute::aINT) ? 6 : 0;
                m_attribute_spr_natg = (m_natural_genius_a1 == eAttribute::aSPR) ? 6 : 0;
                m_attribute_wis_natg = (m_natural_genius_a1 == eAttribute::aWIS) ? 6 : 0;
                ui->comboBox_natural_genius_a1->setCurrentIndex(static_cast<int>(m_natural_genius_a1));
                break;
            }
        }
    }
    if (m_natural_genius_a3 == m_natural_genius_a2)
    {
        for (uint32_t i = 0; i < m_numAttributes; i++)
        {
            if ((i != m_natural_genius_a3) && (i != m_natural_genius_a1))
            {
                m_natural_genius_a2 = intToAttribute(static_cast<int>(i));
                ui->comboBox_natural_genius_a2->setCurrentIndex(static_cast<int>(m_natural_genius_a2));
                break;
            }
        }
    }
    ui->comboBox_natural_genius_a1->blockSignals(blocked_a1);
    ui->comboBox_natural_genius_a2->blockSignals(blocked_a2);
    ui->comboBox_natural_genius_a3->blockSignals(blocked_a3);
    m_calculateBattleStats();
}

void MainWindow::on_comboBox_armor_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
            m_armor = eArmor::aLight;
            ui->comboBox_attribute_physical_defense->setCurrentIndex(attributeToInt(eAttribute::aDEX));
        break;
        case 1:
            m_armor = eArmor::aHeavy;
            ui->comboBox_attribute_physical_defense->setCurrentIndex(attributeToInt(eAttribute::aCON));
        break;
    }
    m_calculateBattleStats();
}

void MainWindow::on_comboBox_weapon_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
            m_weapon = eWeapon::wLight;
            ui->comboBox_attribute_physical_attack->setCurrentIndex(attributeToInt(eAttribute::aDEX));
        break;
        case 1:
            m_weapon = eWeapon::wHeavy;
            ui->comboBox_attribute_physical_attack->setCurrentIndex(attributeToInt(eAttribute::aSTR));
        break;
    }
    m_calculateBattleStats();
}

void MainWindow::on_comboBox_attribute_physical_attack_currentIndexChanged(int index)
{
    m_physical_attack = intToAttribute(index);
    m_calculateBattleStats();
}

void MainWindow::on_comboBox_attribute_physical_defense_currentIndexChanged(int index)
{
    m_physical_defense = intToAttribute(index);
    m_calculateBattleStats();
}

void MainWindow::on_checkBox_default_attributes_clicked()
{
    if (ui->checkBox_default_attributes->isChecked())
    {
        ui->checkBox_default_attributes->setChecked(true);
        m_default_attributes = true;
        ui->comboBox_attribute_physical_attack->setEnabled(false);
        if (m_weapon == eWeapon::wLight)
        {
            ui->comboBox_attribute_physical_attack->setCurrentIndex(attributeToInt(eAttribute::aDEX));
        }
        else
        {
            ui->comboBox_attribute_physical_attack->setCurrentIndex(attributeToInt(eAttribute::aSTR));
        }
        if (m_armor == eArmor::aLight)
        {
            ui->comboBox_attribute_physical_attack->setCurrentIndex(attributeToInt(eAttribute::aDEX));
        }
        else
        {
            ui->comboBox_attribute_physical_defense->setCurrentIndex(attributeToInt(eAttribute::aCON));
        }
        ui->comboBox_attribute_physical_defense->setEnabled(false);
    }
    else
    {
        ui->checkBox_default_attributes->setChecked(false);
        m_default_attributes = false;
        ui->comboBox_attribute_physical_attack->setEnabled(true);
        ui->comboBox_attribute_physical_defense->setEnabled(true);
    }
    m_calculateBattleStats();
}

void MainWindow::on_comboBox_hp_mp_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
            m_default_hp = true;
        break;
        case 1:
            m_default_hp = false;
        break;
    }
    m_calculate();
}
