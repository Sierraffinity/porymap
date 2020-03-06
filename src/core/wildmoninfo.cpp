#include "wildmoninfo.h"
#include "montabwidget.h"



WildMonInfo getDefaultMonInfo(EncounterField field, int timesCount) {
    WildMonInfo newInfo;
    newInfo.active = true;
    newInfo.encounterRate = 0;

    while (timesCount--)
    {
        QVector<WildPokemon> timeMons;
        int size = field.encounterRates.size();
        while (size--)
        {
            timeMons.append(WildPokemon());
        }
        newInfo.wildPokemon.append(timeMons);
    }

    return newInfo;
}

WildMonInfo copyMonInfoFromTab(QTableWidget *monTable, EncounterField monField, QVector<QVector<WildPokemon>> mons, int timeOfDay) {
    WildMonInfo newInfo;
    QVector<WildPokemon> newWildMons;

    bool extraColumn = !monField.groups.isEmpty();
    for (int row = 0; row < monTable->rowCount(); row++) {
        WildPokemon newWildMon;
        newWildMon.species = monTable->cellWidget(row, extraColumn ? 2 : 1)->findChild<QComboBox *>()->currentText();
        newWildMon.minLevel = monTable->cellWidget(row, extraColumn ? 3 : 2)->findChild<QSpinBox *>()->value();
        newWildMon.maxLevel = monTable->cellWidget(row, extraColumn ? 4 : 3)->findChild<QSpinBox *>()->value();
        newWildMons.append(newWildMon);
    }
    mons[timeOfDay] = newWildMons;
    newInfo.active = true;
    newInfo.wildPokemon = mons;
    newInfo.encounterRate = monTable->findChild<QSpinBox *>()->value();

    return newInfo;
}
