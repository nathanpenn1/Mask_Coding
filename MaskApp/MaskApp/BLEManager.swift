//
//  BLEManager.swift
//  MaskApp
//
//  Created by David Nikiforov on 2/12/21.
//

import Foundation
import CoreBluetooth

let nanoServiceCBUUID = CBUUID(string: "180C")
let percentageCBUUID = CBUUID(string: "2A57")
let xvalueCBUUID = CBUUID(string: "2A59")
let yvalueCBUUID = CBUUID(string: "2A58")
let buttonOnOfCBUUID = CBUUID(string: "111E")

struct Peripheral: Identifiable {
    let id: Int
    let name: String
    let rssi: Int
}

class BLEManager: NSObject, ObservableObject, CBCentralManagerDelegate, CBPeripheralDelegate {
    var myCentral: CBCentralManager!
    var nanoPeripheral: CBPeripheral!
    var button: CBCharacteristic!
    @Published var isSwitchedOn = false
    @Published var peripherals = [Peripheral]()
    @Published var percentageVal = 0
    @Published var yVal: [Double] = []
    @Published var xVal = 0
    @Published var buttonOnOff = 0
    @Published var strOut = " "
    @Published var rawVoltage = 0.0
    var inc = 0
    
    override init(){
        super.init()
        myCentral = CBCentralManager(delegate: self, queue: nil)
        //myCentral.scanForPeripherals(withServices: [nanoServiceCBUUID])
        myCentral.delegate = self
    }
    
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        if central.state == .poweredOn {
            print("BLE powered on")
            isSwitchedOn = true
            myCentral.scanForPeripherals(withServices: [nanoServiceCBUUID])
        }
        else {
            isSwitchedOn = false
            print("Something wrong with BLE")
        }
    }
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        print(peripheral)
        nanoPeripheral = peripheral
        nanoPeripheral.delegate = self
        myCentral.stopScan()
        myCentral.connect(nanoPeripheral)
    }
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        print("Connected")
        nanoPeripheral.discoverServices(nil)
    }
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        guard let services = peripheral.services else {return}
        
        for service in services {
            print(service)
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        guard let characteristics = service.characteristics else { return }
        for characteristic in characteristics{
            print(characteristic)
            if characteristic.properties.contains(.read){
                print("\(characteristic.uuid): properties contains .read")
                peripheral.readValue(for: characteristic)
            }
            if characteristic.properties.contains(.notify){
                print("\(characteristic.uuid): properties contains .notify")
                peripheral.setNotifyValue(true, for: characteristic)
            }
            if characteristic.properties.contains(.write){
                print("\(characteristic.uuid): properties contains .write")
                peripheral.setNotifyValue(true, for: characteristic)
            }
            if characteristic.uuid == buttonOnOfCBUUID {
                button = characteristic
            }
        }
    }
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        switch characteristic.uuid {
          case percentageCBUUID:
            print(characteristic.value![0])
            percentageVal = Int(characteristic.value![0])
            rawVoltage = (Double(percentageVal) / 100.0) * 2.875 * 4
            //print(percent)
          case xvalueCBUUID:
            print(characteristic.value![0])
            xVal = Int(characteristic.value![0])
          case yvalueCBUUID:
            let mostSigByte: UInt8 = characteristic.value![1]
            let leastSigByte: UInt8 = characteristic.value![0]
            let value = (UInt16(mostSigByte) << 8 | UInt16(leastSigByte))
            print(value)
            print("\(inc): The inc value")
            if inc < 100 { // 100
                yVal.append(Double(value))
                inc = inc + 1
            }
            else {
                //yVal.remove(at: 0)
                for i in 0..<inc-1 {
                    yVal[i] = yVal[i + 1]
                }
                yVal.remove(at: inc-1)
                yVal.append(Double(value))
            }
            
        case buttonOnOfCBUUID:
            print(characteristic.value![0])
            strOut = "Ready!"
            
          default:
            print("Unhandled Characteristic UUID: \(characteristic.uuid)")
        }
    }
    
    func write(value: Data, characteristic: CBCharacteristic) {
        //self.connectedPeripheral?.writeValue(value, for: characteristic, type: .withResponse)
        // Check if it has the write property
        //if characteristic.properties.contains(.writeWithoutResponse) && nanoPeripheral != nil {

            //nanoPeripheral.writeValue(value, for: characteristic, type: .withoutResponse)
        //}
        nanoPeripheral.writeValue(value, for: characteristic, type: .withResponse)
    }
    
    func peripheral(_ peripheral: CBPeripheral, didWriteValueFor characteristic: CBCharacteristic, error: Error?) {
        print("peripheral: didWriteValueFor")
    }
}
