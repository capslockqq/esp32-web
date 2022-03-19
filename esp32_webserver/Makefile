esp32:
	pio run -e esp32
native:
	pio run -e native
simulate:
	pio run -e simulate
upload:
	pio run -e esp32 -t upload
clean:
	pio run -t clean
test:
	pio test -e native
run_native:
	./.pio/build/native/program
run_simulate:
	./.pio/build/simulate/program