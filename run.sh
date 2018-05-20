root=${PWD}

mkdir -p "${root}/static_analysis"
./how-to-use-pvs-studio-free -c 1 .
pvs-studio-analyzer trace -o "${root}/static_analysis/strace_out" -- make
pvs-studio-analyzer analyze -f "${root}/static_analysis/strace_out" -o "${root}/static_analysis/project.log"
plog-converter -a GA:1,2 -t tasklist -o "${root}/static_analysis/project.tasks" "${root}/static_analysis/project.log"
