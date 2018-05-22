/*=========================================================================

   Program: QCommander

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   QCommander is a free software; you can redistribute it and/or modify it.


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

#include "xaxiscombobox.h"
#include <bmcolumns.h>
#include "globals.h"

XAxisComboBox::XAxisComboBox(BmColumns* bmColumns, QWidget* parent)
    : QComboBox(parent) {
  auto& colAttrs = bmColumns->getColPlotAttrs();
  for (auto key : colAttrs.keys()) {
    if (colAttrs[key] == BmColumns::ColumnPlotAttr::X_AXIS) {
      addItem(bmColumns->columnNameToString(key));
      m_bmColumnList.append(key);
    }
  }

  connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged),
          [=](int index) {
            if (index >= 0 && index < m_bmColumnList.size())
              emit currentColumnChanged(m_bmColumnList.at(index));
          });
}

void XAxisComboBox::update(BmColumns* bmColumns) {
  auto& colAttrs = bmColumns->getColPlotAttrs();
  clear();
  m_bmColumnList.clear();
  for (auto key : colAttrs.keys()) {
    if (colAttrs[key] == BmColumns::ColumnPlotAttr::X_AXIS) {
      addItem(bmColumns->columnNameToString(key));
      m_bmColumnList.append(key);
    }
  }
}
