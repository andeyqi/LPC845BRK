#python -m pip install -U prettytable
####      或者
#pip install -U prettytable

from prettytable import PrettyTable
x = PrettyTable()

x.title = 'Memory space'
x.field_names = ["Memory type", "Addr"]
x.add_row(["(reserved)", "0xE010 0000~0xFFFF FFFF"])
x.add_row(["private peripheral bus", "0xE000 0000~0xE010 0000"])
x.add_row(["(reserved)", "0xA000 8000~0xE000 0000"])
x.add_row(["GPIO interrupts", "0xA000 4000~0xA000 8000"])
x.add_row(["GPIO", "0xA000 0000~0xA000 4000"])
x.add_row(["(reserved)", "0x5001 4000~0xA000 0000"])
x.add_row(["AHB peripherals", "0x5000 0000~0x5001 4000"])
x.add_row(["(reserved)", "0x4008 0000~0x5000 0000"])
x.add_row(["APB peripherals", "0x4000 0000~0x4000 8000"])
x.add_row(["(reserved)", "0x1000 4000~0x4000 0000"])
x.add_row(["RAM1", "0x1000 2000~0x1000 4000"])
x.add_row(["RAM0", "0x1000 0000~0x1000 2000"])
x.add_row(["(reserved)", "0x0F00 5000~0x1000 0000"])
x.add_row(["Boot ROM", "0x0F00 0000~0x0F00 4000"])
x.add_row(["(reserved)", "0x0001 0000~0x0F00 0000"])
x.add_row(["Flash memory", "0x0000 0000~0x0000 1000"])
print(x)

y = PrettyTable()
y.title = 'AHB perpherals'
y.field_names = ["Perpheral type", "Addr"]
y.add_row(["FAIM memory", "0x5001 0000~0x5001 4000"])
y.add_row(["MTB registers", "0x5000 C000~0x5001 0000"])
y.add_row(["DMA controller", "0x5000 8000~0x5000 C000"])
y.add_row(["SCTimer / PWM", "0x5000 4000~0x5000 8000"])
y.add_row(["CRC engine", "0x5000 0000~0x5000 4000"])
print(y)


z = PrettyTable()
z.title = 'APB perpherals'
z.field_names = ["Perpheral type", "Addr"]
z.add_row(["(reserved)", "0x4007 8000~0x4008 0000"])
z.add_row(["UART4", "0x4007 4000~0x4007 8000"])
z.add_row(["UART3", "0x4007 0000~0x4007 4000"])
z.add_row(["UART2", "0x4006 C000~0x4007 0000"])
z.add_row(["UART1", "0x4006 8000~0x4006 C000"])
z.add_row(["UART0", "0x4006 4000~0x4006 8000"])
z.add_row(["CapTouch", "0x4006 0000~0x4006 4000"])
z.add_row(["SPI1", "0x4005 C000~0x4006 0000"])
z.add_row(["SPI0", "0x4005 8000~0x4005 C000"])
z.add_row(["I2C1", "0x4005 4000~0x4005 8000"])
z.add_row(["I2C0", "0x4005 0000~0x4005 4000"])
z.add_row(["(reserved)", "0x4004 C000~0x4005 0000"])
z.add_row(["Syscon", "0x4004 8000~0x4004 C000"])
z.add_row(["IOCON", "0x4004 4000~0x4004 8000"])
z.add_row(["Flash controller", "0x4004 0000~0x4004 4000"])
z.add_row(["(reserved)", "0x4003 C000~0x4004 0000"])
z.add_row(["CTIMER 0", "0x4003 8000~0x4003 C000"])
z.add_row(["I2C3", "0x4003 4000~0x4003 8000"])
z.add_row(["I2C2", "0x4003 0000~0x4003 4000"])
z.add_row(["Input Multiplexing", "0x4002 C000~0x4003 0000"])
z.add_row(["(reserved)", "0x4002 8000~0x4002 C000"])
z.add_row(["Analog Comparator", "0x4002 4000~0x4002 8000"])
z.add_row(["PMU", "0x4002 0000~0x4002 4000"])
z.add_row(["ADC", "0x4001 C000~0x4002 0000"])
z.add_row(["DAC1", "0x4001 8000~0x4001 C000"])
z.add_row(["DAC0", "0x4001 4000~0x4001 8000"])
z.add_row(["FAIM controller", "0x4001 0000~0x4001 4000"])
z.add_row(["Switch Matrix", "0x4000 C000~0x4001 0000"])
z.add_row(["Wake-up Timer", "0x4000 8000~0x4000 C000"])
z.add_row(["Multi-Rate Timer", "0x4000 4000~0x4000 8000"])
z.add_row(["Watchdog timer", "0x4000 0000~0x4000 4000"])
print(z)