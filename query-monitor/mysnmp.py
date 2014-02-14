import netsnmp

class snmpSessionBaseClass(object):
    'A Base Class For a SNMP Session'
    def __init__(self,
                oid=".1.3.6.1.4.1.33332.1",
                Version=2,
                DestHost="localhost",
                Community="ling"):

        self.oid = oid
        self.Version = Version
        self.DestHost = DestHost
        self.Community = Community


    def query(self):
        'Creates SNMP query session'
        try:
            result = netsnmp.snmpwalk(self.oid,
                                    Version = self.Version,
                                    DestHost = self.DestHost,
                                    Community = self.Community)
        except:
            import sys
            print sys.exc_info()
            result = None

        return result

def test():
    'test function'
    foo = snmpSessionBaseClass(DestHost="192.168.254.133",Community="yidong")
    result = foo.query()
    print result 

if __name__ == '__main__':
    test()
