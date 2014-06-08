var GpioPin = require('./build/Release/GPIOPin.node');

var sensor = new GpioPin({
   pin: 23,
   direction: 1
});

sensor.write(1);
