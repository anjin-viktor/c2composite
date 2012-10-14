set comp_path "../src/c2composite"

if {[file exists $comp_path] == 0} {
	puts stderr "$comp_path not exists";
	exit 1;
}

set test_cases_path "./"
set source_files  [glob -directory $test_cases_path -nocomplain -tail *.c]

foreach item $source_files {
	set res_file $item.Res
	set true_file $item.Nrm

	catch {
		exec $comp_path $item $res_file
	} res


	set stream [open $true_file r]
	fconfigure $stream -translation binary
	set true_res [read $stream] 
	close $stream

	set stream [open $res_file r]
	fconfigure $stream -translation binary
	set res [read $stream] 
	close $stream


	if {$res != $true_res} {
		puts stdout "test $item failed";
		exit 1;
	}
}

set source_files  [glob -directory $test_cases_path -nocomplain -tail *.c.Res]

foreach item $source_files {
	file delete $item
}


puts "tests passed fine"
exit 0;
