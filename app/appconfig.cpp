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

#include "appconfig.h"

void loadAppSettings() {
  QSettings::setDefaultFormat(QSettings::IniFormat);
}

QStringList readRecentFiles() {
  QSettings appSettings;
  appSettings.beginGroup("recent-files");
  QString temp = appSettings.value("files").toString();
  QStringList recentFiles;
  recentFiles << temp.split(" ");
  appSettings.endGroup();
  return recentFiles;
}

void updateRecentFiles(QString fileName) {
  QSettings appSettings;
  appSettings.beginGroup("recent-files");
  QString temp = appSettings.value("files").toString();
  QStringList recentFiles;
  recentFiles << temp.split(" ");
  if (recentFiles.contains(fileName)) {
    recentFiles.removeOne(fileName);
  }
  recentFiles.push_front(fileName);
  if (recentFiles.size() > 5)
    recentFiles.pop_back();
  appSettings.setValue("files", recentFiles.join(" "));

  // appSettings.setValue("files", ""); // to reset recent file list
  appSettings.endGroup();
}
