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

#include "benchmarkdelegate.h"
#include <QApplication>
#include <QCheckBox>
#include <QMouseEvent>

static QRect CheckBoxRect(const QStyleOptionViewItem& view_item_style_options) {
  QStyleOptionButton check_box_style_option;
  QRect check_box_rect = QApplication::style()->subElementRect(
      QStyle::SE_CheckBoxIndicator, &check_box_style_option);
  QPoint check_box_point(view_item_style_options.rect.x() +
                             view_item_style_options.rect.width() / 2 -
                             check_box_rect.width() / 2,
                         view_item_style_options.rect.y() +
                             view_item_style_options.rect.height() / 2 -
                             check_box_rect.height() / 2);
  return QRect(check_box_point, check_box_rect.size());
}

BenchmarkDelegate::BenchmarkDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}

bool BenchmarkDelegate::editorEvent(QEvent* event,
                                    QAbstractItemModel* model,
                                    const QStyleOptionViewItem& option,
                                    const QModelIndex& index) {
  if (index.column() == 0) {
    if ((event->type() == QEvent::MouseButtonRelease) ||
        (event->type() == QEvent::MouseButtonDblClick)) {
      QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
      if (mouse_event->button() != Qt::LeftButton ||
          !CheckBoxRect(option).contains(mouse_event->pos())) {
        return false;
      }
      if (event->type() == QEvent::MouseButtonDblClick) {
        return true;
      }
    } else if (event->type() == QEvent::KeyPress) {
      if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
          static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select) {
        return false;
      }
    } else {
      return false;
    }

    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
    return model->setData(index, !checked, Qt::EditRole);
  } else {
    return QStyledItemDelegate::editorEvent(event, model, option, index);
  }
}

void BenchmarkDelegate::paint(QPainter* painter,
                              const QStyleOptionViewItem& option,
                              const QModelIndex& index) const {
  if (index.column() == 0) {
    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

    QStyleOptionButton check_box_style_option;
    check_box_style_option.state |= QStyle::State_Enabled;
    if (checked) {
      check_box_style_option.state |= QStyle::State_On;
    } else {
      check_box_style_option.state |= QStyle::State_Off;
    }
    check_box_style_option.rect = CheckBoxRect(option);

    QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                       &check_box_style_option, painter);
  } else {
    QStyledItemDelegate::paint(painter, option, index);
  }
}
