# emon-meter
Pulse counting and timer node for the OpenEnergyMonitor ecosystem.

This sketch turns a pro mini + RFM69 radio combo into a custom OpenEnergyMonitor node.
The node communicates via radio with the emonPi radio to report pulse inputs received from pulse meters (water, fuel, electricity...).
The sketch also supports tracking "on time" of an appliance, by generating pulses at a configurable rate as long as an input pin is HIGH.

Hardware:
- a power supply (e.g. 5V USB into the pro mini Raw input). Battery operation is out since the sketch monitors digital pins in a tight loop.
- An Arduino pro min, 3.3V 8MHz. The 5V / 16MHz version would require a 3.3V regulator for the RFM69m which is *not* 5V compatible
- An RFM69 W/CW (or any radio you manage to get working with the JeeLib library)

Software:
- The sketch has been tested with the OpenEnergyMonitor of the JeeLib library:
  https://github.com/openenergymonitor/jeelib
  The radio may or may not work with other versions of the JeeLib library.
  
See EmonMeter.ino for configuration of the inputs. All counters are reported to emonHub as 32 bit unsigned longs, sp the emonHub config entry will look something like this:

[[18]]
    nodename = emonmeter
    [[[rx]]]
        names = fuel,plaque,water
        datacodes = L,L,L
        scales = 1,1,1
        units = ml,Wh,l
