
all:
	(cd cmd && make)
	(cd jennyribeiro-hw01 && make)
	(cd plugins/car_control && make)

clean:
	(cd cmd && make clean)
	(cd jennyribeiro-hw01 && make clean)
	(cd plugins/car_control && make clean)

.PHONY: all clean
