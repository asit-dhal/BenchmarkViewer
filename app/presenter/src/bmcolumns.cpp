/*=========================================================================

   Program: BenchmarkViewer

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   BenchmarkViewer is a free software; you can redistribute it and/or modify it.


   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/

#include "bmcolumns.h"
#include <QObject>
#include "globals.h"

BmColumns::BmColumns(QObject* parent) : QObject(parent) {
  m_columnName[Columns::STATUS] = tr("Status");
  m_columnName[Columns::NAME] = tr("Name");
  m_columnName[Columns::ITERATIONS] = tr("Iterations");
  m_columnName[Columns::REAL_TIME] = tr("Realtime");
  m_columnName[Columns::CPU_TIME] = tr("Cpu Time");
  m_columnName[Columns::TIME_UNIT] = tr("Timeunit");
  m_columnName[Columns::FILENAME] = tr("Filename");

  m_columnViewStatus[Columns::STATUS] = true;
  m_columnViewStatus[Columns::NAME] = true;
  m_columnViewStatus[Columns::ITERATIONS] = true;
  m_columnViewStatus[Columns::REAL_TIME] = true;
  m_columnViewStatus[Columns::CPU_TIME] = true;
  m_columnViewStatus[Columns::TIME_UNIT] = true;
  m_columnViewStatus[Columns::FILENAME] = true;

  m_columnIndex[Columns::STATUS] = 0;
  m_columnIndex[Columns::NAME] = 1;
  m_columnIndex[Columns::ITERATIONS] = 2;
  m_columnIndex[Columns::REAL_TIME] = 3;
  m_columnIndex[Columns::CPU_TIME] = 4;
  m_columnIndex[Columns::TIME_UNIT] = 5;
  m_columnIndex[Columns::FILENAME] = 6;

  qCDebug(gui)
      << "signal[BmColumns::hideColumn] -> slot[BmColumns::onHideColumn]";
  connect(this, &BmColumns::hideColumn, this, &BmColumns::onHideColumn);
  qCDebug(gui)
      << "signal[BmColumns::showColumn] -> slot[BmColumns::onShowColumn]";
  connect(this, &BmColumns::showColumn, this, &BmColumns::onShowColumn);

  qCDebug(gui) << m_columnName;
}

QString BmColumns::columnNameToString(Columns cols) {
  return m_columnName[cols];
}
int BmColumns::columnNameToIndex(Columns cols) {
  return m_columnIndex[cols];
}

void BmColumns::onHideColumn(Columns col) {
  qCDebug(gui) << "col name: " << columnNameToString(col)
               << " index: " << columnNameToIndex(col);
  m_columnViewStatus[col] = false;
}

void BmColumns::onShowColumn(Columns col) {
  qCDebug(gui) << "col name: " << columnNameToString(col)
               << " index: " << columnNameToIndex(col);
  m_columnViewStatus[col] = true;
}

bool BmColumns::isColumnHidden(Columns col) {
  return m_columnViewStatus[col] == false;
}

BmColumns::Columns BmColumns::indexToColumns(int index) {
  switch (index) {
    case 0:
      return Columns::STATUS;
    case 1:
      return Columns::NAME;
    case 2:
      return Columns::ITERATIONS;
    case 3:
      return Columns::REAL_TIME;
    case 4:
      return Columns::CPU_TIME;
    case 5:
      return Columns::TIME_UNIT;
    case 6:
      return Columns::FILENAME;
    default:
      return Columns::INVALID;
  }
}

QDebug operator<<(QDebug d, const BmColumns::Columns& col) {
  switch (col) {
    case BmColumns::Columns::INVALID:
      d << "INVALID";
      break;
    case BmColumns::Columns::STATUS:
      d << "STATUS";
      break;
    case BmColumns::Columns::NAME:
      d << "NAME";
      break;
    case BmColumns::Columns::ITERATIONS:
      d << "ITERATIONS";
      break;
    case BmColumns::Columns::REAL_TIME:
      d << "REAL_TIME";
      break;
    case BmColumns::Columns::CPU_TIME:
      d << "CPU_TIME";
      break;
    case BmColumns::Columns::TIME_UNIT:
      d << "TIME_UNIT";
      break;
    case BmColumns::Columns::FILENAME:
      d << "FILENAME";
      break;
  }
  return d;
}