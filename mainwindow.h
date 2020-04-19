#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_checkBox_secluded_training_clicked();

        void on_checkBox_natural_genius_clicked();

        void on_comboBox_class_currentIndexChanged(int index);

        void on_comboBox_growth_curve_currentIndexChanged(int index);

        void on_spinBox_level_valueChanged(int arg1);

        void on_pushButton_strength_inc_clicked();

        void on_pushButton_strength_dec_clicked();

        void on_pushButton_constitution_inc_clicked();

        void on_pushButton_constitution_dec_clicked();

        void on_pushButton_dexterity_inc_clicked();

        void on_pushButton_dexterity_dec_clicked();

        void on_pushButton_intelligence_inc_clicked();

        void on_pushButton_intelligence_dec_clicked();

        void on_pushButton_spirit_inc_clicked();

        void on_pushButton_spirit_dec_clicked();

        void on_pushButton_wisdom_inc_clicked();

        void on_pushButton_wisdom_dec_clicked();

        void on_comboBox_natural_genius_a1_currentIndexChanged(int index);

        void on_comboBox_natural_genius_a2_currentIndexChanged(int index);

        void on_comboBox_natural_genius_a3_currentIndexChanged(int index);

        void on_comboBox_armor_currentIndexChanged(int index);

        void on_comboBox_weapon_currentIndexChanged(int index);

        void on_comboBox_attribute_physical_attack_currentIndexChanged(int index);

        void on_comboBox_attribute_physical_defense_currentIndexChanged(int index);

        void on_checkBox_default_attributes_clicked();

        void on_comboBox_hp_mp_currentIndexChanged(int index);

private:
        Ui::MainWindow *ui;
        void m_calculateBattleStats(void);
        void m_calculate(void);

        uint32_t m_level = 1;

        uint32_t m_attribute_points = 24;
        uint32_t m_skill_points     = 3;
        uint32_t m_gold             = 225;
        uint32_t m_gold_bracket[11] = {50, 175, 300, 600, 850, 1100, 2200, 2575, 2950, 6000, 15000};

        bool m_natural_genius     = false;
        bool m_secluded_training  = false;
        bool m_default_attributes = true;
        bool m_default_hp         = true;

        enum eClass:uint32_t {archer = 0, mage = 1, fighter = 2};
        eClass m_class = eClass::archer;

        enum eGrowthCurve:uint32_t {balanceCurve = 0, resourceCurve = 1, skillCurve = 2, attributeCurve = 3};
        eGrowthCurve m_growthCurve =balanceCurve;

        enum eArmor:uint32_t {aLight = 0, aHeavy = 1};
        eArmor m_armor = eArmor::aLight;

        enum eWeapon:uint32_t {wLight = 0, wHeavy = 1};
        eWeapon m_weapon = eWeapon::wLight;

        enum eAttribute:uint32_t {aSTR = 0, aCON = 1, aDEX = 2, aINT = 3, aSPR = 4, aWIS = 5, aCount = 6};
        eAttribute intToAttribute(int _value);
        int        attributeToInt(MainWindow::eAttribute _attribute);
        eAttribute m_natural_genius_a1 = eAttribute::aSTR;
        eAttribute m_natural_genius_a2 = eAttribute::aCON;
        eAttribute m_natural_genius_a3 = eAttribute::aDEX;
        eAttribute m_physical_attack   = eAttribute::aDEX;
        eAttribute m_physical_defense  = eAttribute::aDEX;

        const uint32_t m_numAttributes = 6;
        uint32_t m_attribute_str      = 8; // total = base + norm + naatg
        uint32_t m_attribute_str_base = 8; // base starting attributes
        uint32_t m_attribute_str_norm = 0; // normally assignes attribute points
        uint32_t m_attribute_str_natg = 0; // natural genius assigned attribute points
        uint32_t m_attribute_con      = 8;
        uint32_t m_attribute_con_base = 8;
        uint32_t m_attribute_con_norm = 0;
        uint32_t m_attribute_con_natg = 0;
        uint32_t m_attribute_dex      = 8;
        uint32_t m_attribute_dex_base = 8;
        uint32_t m_attribute_dex_norm = 0;
        uint32_t m_attribute_dex_natg = 0;
        uint32_t m_attribute_int      = 8;
        uint32_t m_attribute_int_base = 8;
        uint32_t m_attribute_int_norm = 0;
        uint32_t m_attribute_int_natg = 0;
        uint32_t m_attribute_spr      = 8;
        uint32_t m_attribute_spr_base = 8;
        uint32_t m_attribute_spr_norm = 0;
        uint32_t m_attribute_spr_natg = 0;
        uint32_t m_attribute_wis      = 8;
        uint32_t m_attribute_wis_base = 8;
        uint32_t m_attribute_wis_norm = 0;
        uint32_t m_attribute_wis_natg = 0;

        uint32_t m_battleStat_hp      = 21; // total = base + norm + gear
        uint32_t m_battleStat_hp_base = 21; // base starting points
        uint32_t m_battleStat_hp_norm = 0;  // normally assigned points
        uint32_t m_battleStat_hp_gear = 0;  // points from attributes based on gear
        uint32_t m_battleStat_mp      = 21;
        uint32_t m_battleStat_mp_base = 21;
        uint32_t m_battleStat_mp_norm = 0;
        uint32_t m_battleStat_mp_gear = 0;
        uint32_t m_battleStat_pa      = 0;
        uint32_t m_battleStat_pa_base = 0;
        uint32_t m_battleStat_pa_norm = 0;
        uint32_t m_battleStat_pa_gear = 0;
        uint32_t m_battleStat_ma      = 0;
        uint32_t m_battleStat_ma_base = 0;
        uint32_t m_battleStat_ma_norm = 0;
        uint32_t m_battleStat_ma_gear = 0;
        uint32_t m_battleStat_pd      = 10;
        uint32_t m_battleStat_pd_base = 10;
        uint32_t m_battleStat_pd_norm = 0;
        uint32_t m_battleStat_pd_gear = 0;
        uint32_t m_battleStat_md      = 10;
        uint32_t m_battleStat_md_base = 10;
        uint32_t m_battleStat_md_norm = 0;
        uint32_t m_battleStat_md_gear = 0;
};

#endif // MAINWINDOW_H
