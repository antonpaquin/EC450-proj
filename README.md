# EC450-proj

MSP432 GC TAS bot

(abbrev. notes)

### todo
might probe a live controller via timerA capture
oscilloscope stuff

### protocol
pullup resistor on 3,3V (blue?)
console sends "000000001" every 12ms when no controllers connected
  gc controller responds with something
afterwards, controller queries with "0100 0000 0000 0011 0000 0010"
  gets 64 bit response
terminate everything with a stop bit (1)
3.95us/bit

http://www.int03.co.uk/crema/hardware/gamecube/gc-control.html
