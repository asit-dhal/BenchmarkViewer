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

#include "model/context.h"

namespace model {

QDateTime Context::getTimestamp() const {
  return timestamp;
}

void Context::setTimestamp(const QDateTime& value) {
  timestamp = value;
}

int Context::getCpuFrequency() const {
  return cpuFrequency;
}

void Context::setCpuFrequency(int value) {
  cpuFrequency = value;
}

bool Context::getCpuScalingEnabled() const {
  return cpuScalingEnabled;
}

void Context::setCpuScalingEnabled(bool value) {
  cpuScalingEnabled = value;
}

QString Context::getLibraryBuildType() const {
  return libraryBuildType;
}

void Context::setLibraryBuildType(QString value) {
  libraryBuildType = value;
}

int Context::getCpuCount() const {
  return cpuCount;
}

void Context::setCpuCount(int value) {
  cpuCount = value;
}

QDebug operator<<(QDebug d, const Context& ctx) {
  d << "timestamp: " << ctx.getTimestamp()
    << " cpu_count: " << ctx.getCpuCount()
    << " cpu_frequency: " << ctx.getCpuFrequency()
    << " cpu_scaling_enabled: " << ctx.getCpuScalingEnabled()
    << " library_build_type: " << ctx.getLibraryBuildType();
  return d;
}

}  // namespace model
