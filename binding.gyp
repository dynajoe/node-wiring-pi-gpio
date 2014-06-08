{
	"targets": [
		{
			"target_name":  "GPIOPin",
			"sources":      [ "src/addon.cc", "src/gpio_pin.cc" ],
			"include_dirs": [ "../lib/wiringPi/wiringPi" ],
			"ldflags":      [ "-lwiringPi" ]
		}
	]
}
