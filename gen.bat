set QT_MESSAGE_PATTERN="%{time h:mm:ss.zzz}%{threadid}%{if-category} %{category}%{endif} %{type}%{if-debug} %{file}:%{line} %{function} %{endif} %{message}"

if not exist C:\VTS\NUL mkdir build
cd build 
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH="c:/Qt/5.11.2/msvc2017_64" -DCMAKE_BUILD_TYPE=Debug ..
start "" "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe" C:\proj\BenchmarkViewer\build\BenchmarkViewer.sln