#include "framemodel.hpp"
#include "common.hpp"
#include <QDebug>

FrameModel::FrameModel(QObject *parent)
    : QAbstractTableModel(parent),
      brushBlack(Qt::black),
      brushWhite(Qt::white),
      brushCyan(Qt::cyan),
      brushMagenta(Qt::magenta),
      brushBrown(QColor(190, 110, 0)),
      brushRed(Qt::red),
      brushDarkRed(Qt::darkRed),
      brushDarkGray(Qt::darkGray),
      brushBlue(Qt::blue)
{
    boldFont.setBold(true);
    italicFont.setItalic(true);
}

int FrameModel::rowCount(const QModelIndex &) const
{
    return hltasInput.GetFrames().size();
}

int FrameModel::columnCount(const QModelIndex &) const
{
    return IndLength;
}

QVariant FrameModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return getDataText(index.row(), index.column(), role);
    else if (role == Qt::BackgroundRole)
        return getDataBackground(index.row(), index.column());
    else if (role == Qt::ForegroundRole)
        return getDataForeground(index.row(), index.column());
    else if (role == Qt::TextAlignmentRole) {
        if (isSaveLine(index.row()) && index.column() == 0)
            return (QVariant)(Qt::AlignLeft | Qt::AlignVCenter);
        if (index.column() == IndCmds)
            return (QVariant)(Qt::AlignLeft | Qt::AlignVCenter);
        else if (index.column() == IndNumRepeat)
            return (QVariant)(Qt::AlignRight | Qt::AlignVCenter);
        else
            return Qt::AlignCenter;
    } else if (role == Qt::FontRole)
        return getDataFont(index.row(), index.column());

    return QVariant();
}

QVariant FrameModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole)
            return getHHeaderText(section);
        else if (role == Qt::TextAlignmentRole && section == IndCmds)
            return Qt::AlignLeft;
    } else if (orientation == Qt::Vertical) {
        if (role == Qt::DisplayRole)
            return cumulativeFrameNums[section];
        else if (role == Qt::TextAlignmentRole)
            return (QVariant)(Qt::AlignRight | Qt::AlignVCenter);
    }

    return QVariant();
}

bool FrameModel::setData(const QModelIndex &index, const QVariant &value,
                         int role)
{
    if (role != Qt::EditRole)
        return false;

    HLTAS::Frame &frame = hltasInput.GetFrame(index.row());

    switch (index.column()) {
    case IndNumRepeat:
        frame.SetRepeats(value.toUInt());
        updateCumulativeFrameNums();
        break;
    case IndStrafeInfo: {
        QString input = value.toString();

        if (input[0] == '-') {
            frame.Strafe = false;
            break;
        } else if (input[0] == 'A')
            frame.SetType(HLTAS::MAXACCEL);
        else if (input[0] == 'D')
            frame.SetType(HLTAS::MAXDECCEL);
        else if (input[0] == 'C')
            frame.SetType(HLTAS::CONSTSPEED);
        else if (input[0] == 'G')
            frame.SetType(HLTAS::MAXANGLE);

        if (input[1] == 'N')
            frame.SetDir(HLTAS::LINE);
        else if (input[1] == 'Y')
            frame.SetDir(HLTAS::YAW);
        else if (input[1] == 'P')
            frame.SetDir(HLTAS::POINT);
        else if (input[1] == 'L') {
            frame.SetDir(HLTAS::LEFT);
            frame.SetYawPresent(false);
        } else if (input[1] == 'R') {
            frame.SetDir(HLTAS::RIGHT);
            frame.SetYawPresent(false);
        }

        break;
    }
    case IndAutoJump:
        frame.SetAutojumpTimes(value.toUInt());
        break;
    case IndDuckTap:
        frame.SetDucktapTimes(value.toUInt());
        break;
    case IndLgagst:
        frame.SetLgagstTimes(value.toUInt());
        break;
    case IndJumpBug:
        frame.SetJumpbugTimes(value.toUInt());
        break;
    case IndDB4C:
        frame.SetDbcTimes(value.toUInt());
        break;
    case IndDB4G:
        frame.SetDbgTimes(value.toUInt());
        break;
    case IndDWJ:
        frame.SetDwjTimes(value.toUInt());
        break;
    case IndYaw:
        if (frame.Strafe && frame.GetDir() == HLTAS::POINT) {
            QPointF point = value.toPointF();
            frame.SetX(point.x());
            frame.SetY(point.y());
        } else
            frame.SetYaw(value.toDouble());
        break;
    case IndFrameTime:
        frame.Frametime = value.toString().toStdString();
        break;
    case IndUse:
        frame.Use = !frame.Use;
        break;
    case IndDuck:
        frame.Duck = !frame.Duck;
        break;
    case IndJump:
        frame.Jump = !frame.Jump;
        break;
    case IndAttack:
        frame.Attack1 = !frame.Attack1;
        break;
    case IndAttack2:
        frame.Attack2 = !frame.Attack2;
        break;
    case IndReload:
        frame.Reload = !frame.Reload;
        break;
    case IndForward:
        frame.Forward = !frame.Forward;
        break;
    case IndBack:
        frame.Back = !frame.Back;
        break;
    case IndMoveLeft:
        frame.Left = !frame.Left;
        break;
    case IndMoveRight:
        frame.Right = !frame.Right;
        break;
    case IndMoveUp:
        frame.Up = !frame.Up;
        break;
    case IndMoveDown:
        frame.Down = !frame.Down;
        break;
    case IndCmds:
        frame.Commands = value.toString().toStdString();
        break;
    }

    emit dataChanged(index, index);

    return true;
}

QString FrameModel::getHHeaderText(int section) const
{
    switch (section) {
    case IndNumRepeat: return "n";
    case IndStrafeInfo: return "s";
    case IndAutoJump: return "aj";
    case IndDuckTap: return "dt";
    case IndLgagst: return "lg";
    case IndJumpBug: return "jb";
    case IndDB4C: return "dc";
    case IndDB4G: return "dg";
    case IndDWJ: return "dw";
    case IndYaw: return "y";
    case IndPitch: return "p";
    case IndFrameTime: return "ft";
    case IndUse: return "u";
    case IndDuck: return "d";
    case IndJump: return "j";
    case IndAttack: return "a1";
    case IndAttack2: return "a2";
    case IndReload: return "r";
    case IndForward: return "↑";
    case IndBack: return "↓";
    case IndMoveLeft: return "←";
    case IndMoveRight: return "→";
    case IndMoveUp: return "•";
    case IndMoveDown: return "✕";
    case IndCmds: return "cmds";
    }
    return QString();
}

QString FrameModel::getDataText(int row, int column, int role) const
{
#define INF_OR_NUM(val) (!(val) ? (outstr = "∞") : outstr.setNum(val))

    const HLTAS::Frame frame = hltasInput.GetFrames()[row];
    if (!frame.SaveName.empty()) {
        if (column == 0) {
            QString saveName = QString::fromStdString(frame.SaveName);
            if (role == Qt::DisplayRole)
                return QString("SAVE: %1").arg(saveName);
            else
                return saveName;
        } else
            return QString();
    }

    QString outstr;

    switch (column) {
    case IndNumRepeat:
        outstr.setNum(frame.GetRepeats());
        break;

    case IndStrafeInfo:
        if (!frame.Strafe)
            break;

        if (frame.GetType() == HLTAS::MAXACCEL)
            outstr = 'A';
        else if (frame.GetType() == HLTAS::MAXDECCEL)
            outstr = 'D';
        else if (frame.GetType() == HLTAS::MAXANGLE)
            outstr = 'G';
        else if (frame.GetType() == HLTAS::CONSTSPEED)
            outstr = 'C';

        if (frame.GetDir() == HLTAS::LEFT)
            outstr += 'L';
        else if (frame.GetDir() == HLTAS::RIGHT)
            outstr += 'R';
        else if (frame.GetDir() == HLTAS::YAW)
            outstr += 'Y';
        else if (frame.GetDir() == HLTAS::POINT)
            outstr += 'P';
        else if (frame.GetDir() == HLTAS::LINE)
            outstr += 'N';

        break;
    case IndAutoJump:
        if (frame.Autojump)
            INF_OR_NUM(frame.GetAutojumpTimes());
        break;
    case IndDuckTap:
        if (frame.Ducktap)
            INF_OR_NUM(frame.GetDucktapTimes());
        break;
    case IndLgagst:
        if (frame.Lgagst)
            INF_OR_NUM(frame.GetLgagstTimes());
        break;
    case IndJumpBug:
        if (frame.Jumpbug)
            INF_OR_NUM(frame.GetJumpbugTimes());
        break;
    case IndDB4C:
        if (frame.Dbc)
            INF_OR_NUM(frame.GetDbcTimes());
        break;
    case IndDB4G:
        if (frame.Dbg)
            INF_OR_NUM(frame.GetDbgTimes());
        break;
    case IndDWJ:
        if (frame.Dwj)
            INF_OR_NUM(frame.GetDwjTimes());
        break;
    case IndYaw:
        if (!frame.Strafe) {
            if (frame.GetYawPresent())
                outstr.setNum(frame.GetYaw());
            break;
        }

        if (frame.GetDir() == HLTAS::LEFT || frame.GetDir() == HLTAS::RIGHT)
            outstr = "NA";
        else if (frame.GetDir() == HLTAS::POINT) {
            if (frame.GetYawPresent())
                outstr = QString("(%1 %2)").arg(frame.GetX()).arg(frame.GetY());
            else
                outstr = "Pending";
        } else if (frame.GetDir() == HLTAS::LINE ||
                   frame.GetDir() == HLTAS::YAW) {
            if (frame.GetYawPresent())
                outstr.setNum(frame.GetYaw());
            else
                outstr = "Pending";
        }
        break;
    case IndPitch:
        if (frame.PitchPresent)
            outstr.setNum(frame.GetPitch());
        break;
    case IndFrameTime:
        outstr = QString::fromStdString(frame.Frametime);
        if (outstr == "-")
            outstr = QString();
        break;
    case IndForward:
        if (frame.Forward)
            outstr = "F";
        break;
    case IndBack:
        if (frame.Back)
            outstr = "B";
        break;
    case IndMoveLeft:
        if (frame.Left)
            outstr = "L";
        break;
    case IndMoveRight:
        if (frame.Right)
            outstr = "R";
        break;
    case IndMoveUp:
        if (frame.Up)
            outstr = "U";
        break;
    case IndMoveDown:
        if (frame.Down)
            outstr = "D";
        break;
    case IndCmds:
        outstr = QString::fromStdString(frame.Commands);
        break;
    }

    return outstr;

#undef INF_OR_NUM
}

Qt::ItemFlags FrameModel::flags(const QModelIndex &index) const
{
    return (QAbstractTableModel::flags(index) | Qt::ItemIsEditable) &
        ~Qt::ItemIsSelectable;
}

QModelIndex FrameModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column);
}

QFont FrameModel::getDataFont(int row, int column) const
{
    HLTAS::Frame frame = hltasInput.GetFrames()[row];

    switch (column) {
    case IndYaw:
        if (frame.Strafe && (frame.GetDir() == HLTAS::LEFT ||
                             frame.GetDir() == HLTAS::RIGHT))
            return italicFont;
        break;
    case IndAutoJump:
    case IndDuckTap:
    case IndLgagst:
    case IndJumpBug:
    case IndDB4C:
    case IndDB4G:
    case IndDWJ:
    case IndForward:
    case IndBack:
    case IndMoveLeft:
    case IndMoveRight:
    case IndMoveUp:
    case IndMoveDown:
        return boldFont;
    }
    return QFont();
}

QBrush FrameModel::getDataBackground(int row, int column) const
{
    const HLTAS::Frame frame = hltasInput.GetFrames()[row];
    if (!frame.SaveName.empty())
        return brushBlack;

    switch (column) {
    case IndUse:
        if (frame.Use)
            return brushBrown;
        break;
    case IndJump:
        if (frame.Jump)
            return brushCyan;
        break;
    case IndDuck:
        if (frame.Duck)
            return brushMagenta;
        break;
    case IndAttack:
        if (frame.Attack1)
            return brushRed;
        break;
    case IndAttack2:
        if (frame.Attack2)
            return brushDarkRed;
        break;
    case IndReload:
        if (frame.Reload)
            return brushDarkGray;
        break;
    }
    return brushWhite;
}

QBrush FrameModel::getDataForeground(int row, int column) const
{
    const HLTAS::Frame frame = hltasInput.GetFrames()[row];
    if (!frame.SaveName.empty())
        return brushWhite;

    switch (column) {
    case IndStrafeInfo:
        return brushBlue;
    case IndDB4C:
        if (frame.GetDbcCeilings())
            return brushRed;
        break;
    case IndLgagst:
        if (frame.GetLgagstFullMaxspeed())
            return brushRed;
        break;
    case IndYaw:
        if (!frame.Strafe)
            break;
        if (frame.GetDir() == HLTAS::LEFT || frame.GetDir() == HLTAS::RIGHT)
            break;
        if (frame.GetYawPresent())
            break;
        return brushRed;
    }
    return QBrush();
}

bool FrameModel::openProject(const QString &fileName)
{
    auto ret = hltasInput.Open(fileName.toStdString());

    // FIXME: Temporary solution for testing purposes.

    if (ret.get().Code != HLTAS::OK) {
        qDebug() << ret.get().Code;
        return false;
    }

    const std::vector<HLTAS::Frame> &frames = hltasInput.GetFrames();
    beginInsertRows(QModelIndex(), 0, frames.size() - 1);
    endInsertRows();
    updateCumulativeFrameNums();
    emit dataChanged(index(0, 0), index(frames.size() - 1, IndLength));

    return true;
}

bool FrameModel::saveProject(const QString &fileName)
{
    // FIXME: Temporary solution
    auto ret = hltasInput.Save(fileName.toStdString());
    if (ret.get().Code != HLTAS::OK)
        qDebug() << ret.get().Code;
    return true;
}

void FrameModel::updateCumulativeFrameNums()
{
    // This can be slow if there is a huge number of framebulks.
    cumulativeFrameNums.clear();
    const std::vector<HLTAS::Frame> &frames = hltasInput.GetFrames();
    cumulativeFrameNums.append(0);
    for (const HLTAS::Frame &frame : frames) {
        cumulativeFrameNums.append(cumulativeFrameNums.last() +
                                   frame.GetRepeats());
    }
    emit headerDataChanged(Qt::Vertical, 0, frames.size() - 1);
}

void FrameModel::insertDuplicateRow(int row)
{
    beginInsertRows(QModelIndex(), row, row);
    HLTAS::Frame frame = hltasInput.GetFrames()[row];
    hltasInput.InsertFrame(row, frame);
    endInsertRows();
    updateCumulativeFrameNums();
}

void FrameModel::insertEmptyRow(int row)
{
    beginInsertRows(QModelIndex(), row, row);
    HLTAS::Frame frame = {};
    frame.SetRepeats(1);
    frame.Frametime = "-";
    hltasInput.InsertFrame(row, frame);
    insertRow(row);
    endInsertRows();
    updateCumulativeFrameNums();
}

bool FrameModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++)
        hltasInput.RemoveFrame(i);
    endRemoveRows();
    updateCumulativeFrameNums();
    return true;
}

void FrameModel::toggleDB4CCeil(int row)
{
    HLTAS::Frame &frame = hltasInput.GetFrame(row);
    frame.SetDbcCeilings(!frame.GetDbcCeilings());
    QModelIndex ind = index(row, IndDB4C);
    emit dataChanged(ind, ind);
}

void FrameModel::toggleLgagstFullM(int row)
{
    HLTAS::Frame &frame = hltasInput.GetFrame(row);
    frame.SetLgagstFullMaxspeed(!frame.GetLgagstFullMaxspeed());
    QModelIndex ind = index(row, IndLgagst);
    emit dataChanged(ind, ind);
}

bool FrameModel::isSaveLine(int row) const
{
    const HLTAS::Frame frame = hltasInput.GetFrames()[row];
    return !frame.SaveName.empty();
}
