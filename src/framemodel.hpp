#ifndef FRAMEMODEL_HPP
#define FRAMEMODEL_HPP

#include <QAbstractTableModel>
#include <QIcon>
#include <QFont>
#include <QBrush>
#include "hltas.hpp"

class FrameModel : public QAbstractTableModel
{
public:
    FrameModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex());

    void insertFramesFromOther(int row, int count, const FrameModel &model);
    void insertDuplicateRow(int row);
    void insertEmptyRow(int row);
    void insertSave(int row);
    bool openProject(const QString &fileName);
    bool saveProject(const QString &fileName = QString());

    void toggleDB4CCeil(int row);
    void toggleLgagstFullM(int row);

    bool isSaveLine(int row) const;

    QString fileName() const;

    QString demoName() const;
    QString saveName() const;
    bool seeds(unsigned int &SSeed, unsigned int &NSSeed) const;

    void setDemoName(const QString &name);
    void setSaveName(const QString &name);
    void setSeeds(unsigned int SSeed, unsigned int NSSeed);

private:
    HLTAS::Input hltasInput;
    QString scriptFileName;
    QVector<unsigned int> cumulativeFrameNums;
    QFont boldFont;
    QFont italicFont;
    QBrush brushBlack;
    QBrush brushWhite;
    QBrush brushCyan;
    QBrush brushMagenta;
    QBrush brushBrown;
    QBrush brushRed;
    QBrush brushDarkRed;
    QBrush brushDarkGray;
    QBrush brushBlue;

    QString getDataText(int row, int column, int role) const;
    QFont getDataFont(int row, int column) const;
    QBrush getDataBackground(int row, int column) const;
    QBrush getDataForeground(int row, int column) const;
    QString getHHeaderText(int section) const;

    void updateCumulativeFrameNums();
};

#endif
