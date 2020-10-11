#!/bin/bash

echo "Listing characteristics"
sudo gatttool -i hci0 -b C3:05:EB:AA:2B:31 -t random --characteristics
echo "(LED)Reading Characteristics"
sudo gatttool -i hci0 -b C3:05:EB:AA:2B:31 -t random --char-read --uuid 19b10001-e8f2-537e-4f6c-d104768a1214
echo "(LED)Writing 01"
sudo gatttool -i hci0 -b C3:05:EB:AA:2B:31 -t random --char-write-req --uuid 19b10001-e8f2-537e-4f6c-d104768a1214 --handle 0x000e --value 01
echo "(LED)Reading"
sudo gatttool -i hci0 -b C3:05:EB:AA:2B:31 -t random --char-read --uuid 19b10001-e8f2-537e-4f6c-d104768a1214
echo "(TEMPERATURE)Reading"
sudo gatttool -i hci0 -b C3:05:EB:AA:2B:31 -t random --char-read --uuid 19b10003-e8f2-537e-4f6c-d104768a1214
echo "(LED)Writing 00"
sudo gatttool -i hci0 -b C3:05:EB:AA:2B:31 -t random --char-write-req --uuid 19b10001-e8f2-537e-4f6c-d104768a1214 --handle 0x000e --value 00


#---------------INTERACTIVE-COMMANDS----------------------
#sudo gatttool -i hci0 -b C3:05:EB:AA:2B:31 -I -t random
#connect
#char-read-uuid 19b10001-e8f2-537e-4f6c-d104768a1214
#char-write-req e 01
#char-read-uuid 19b10001-e8f2-537e-4f6c-d104768a1214
#char-write-req e 00
#char-read-uuid 19b10003-e8f2-537e-4f6c-d104768a1214
#disconnect
#exit
