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

#ifndef CONTEXT_H
#define CONTEXT_H

#include <QDateTime>
#include <QDebug>
#include <QObject>

class Context
{
public:
	Context() = default;
	QDateTime getTimestamp() const;
	void setTimestamp(const QDateTime& value);
	int getCpuFrequency() const;
	void setCpuFrequency(int value);
	bool getCpuScalingEnabled() const;
	void setCpuScalingEnabled(bool value);
	QString getLibraryBuildType() const;
	void setLibraryBuildType(QString value);
	int getCpuCount() const;
	void setCpuCount(int value);

 private:
	QDateTime timestamp;
	int cpuCount;
	int cpuFrequency;
	bool cpuScalingEnabled;
	QString libraryBuildType;
};

QDebug operator<<(QDebug d, const Context& ctx);

#endif  // CONTEXT_H
