use strict;
use warnings;
use LWP::Simple;
use Cwd qw(); 
use File::Basename;
use FindBin qw($Bin);

$ENV{"QT_MESSAGE_PATTERN"} = '%{time h:mm:ss.zzz}%{threadid}%{if-category} %{category}%{endif} %{type}%{if-debug} %{file}:%{line} %{function} %{endif} %{message}';

my $current_path = Cwd::cwd();

my $build_path = "$current_path/build";
mkdir($build_path, 0700) unless(-d $build_path );
chdir($build_path) or die "can't chdir $build_path\n";

my $qt_path = qq("c:/Qt/5.11.2/msvc2017_64");
my $build_type = "Debug";
my $vs_generator = qq("Visual Studio 15 2017 Win64"); 
my $devenv_path = qq("C:\\Program Files\ (x86)\\Microsoft Visual Studio\\2017\\Community\\Common7\\IDE\\devenv.exe");
my $vsproj_path = "$build_path/BenchmarkViewer.sln";

system("cmake -G $vs_generator -DCMAKE_PREFIX_PATH=$qt_path -DCMAKE_BUILD_TYPE=$build_type ..");
exec("$devenv_path $vsproj_path")