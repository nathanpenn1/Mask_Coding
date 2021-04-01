//
//  BLEManager.swift
//  MaskApp
//
//  Created by David Nikiforov on 2/12/21.
//

import Foundation
import CoreBluetooth

let nanoServiceCBUUID = CBUUID(string: "0x180C")
let percentageCBUUID = CBUUID(string: "2A57")
let xvalueCBUUID = CBUUID(string: "2A59")
let yvalueCBUUID = CBUUID(string: "2A58")

struct Peripheral: Identifiable {
    let id: Int
    let name: String
    let rssi: Int
}

class BLEManager: NSObject, ObservableObject, CBCentralManagerDelegate, CBPeripheralDelegate {
    var myCentral: CBCentralManager!
    var nanoPeripheral: CBPeripheral!
    @Published var isSwitchedOn = false
    @Published var peripherals = [Peripheral]()
    @Published var percentageVal = 0
    @Published var yVal: [Double] = []
    @Published var xVal = 0
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
        }
    }
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        switch characteristic.uuid {
          case percentageCBUUID:
            //print(characteristic.value ?? "no value")
            print(characteristic.value![0])
            percentageVal = Int(characteristic.value![0])
            //print(percent)
          case xvalueCBUUID:
            print(characteristic.value![0])
            xVal = Int(characteristic.value![0])
          case yvalueCBUUID:
            print(characteristic.value![0])
            print("\(inc): The inc value")
            if inc < 100 { // 100
                yVal.append(Double(characteristic.value![0]))
                inc = inc + 1
            }
            else {
                //yVal.remove(at: 0)
                for i in 0..<inc-1 {
                    yVal[i] = yVal[i + 1]
                }
                yVal.remove(at: inc-1)
                yVal.append(Double(characteristic.value![0]))
            }
            
          default:
            print("Unhandled Characteristic UUID: \(characteristic.uuid)")
        }
    }
    /*
    private func percentage(from characteristic: CBCharacteristic) -> Int {
        guard let characteristicData = characteristic.value else { return -1 }
        let byteArray = [UInt8](characteristicData)
        let firstBitValue = byteArray[0] & 0x01
        if firstBitValue == 0{
            return Int(byteArray[1])
        }
        else {
            return(Int(byteArray[1]) << 8) + Int(byteArray[2])
        }
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if let pname = peripheral.name{
            print(pname)
            if pname == "Arduino"{
                print("connected to Nano33BLE")
                self.myCentral.stopScan()
                self.myPeripheral = peripheral
                self.myPeripheral.delegate = self
                self.myCentral.connect(peripheral, options: nil)
                //let value = self.myPeripheral.readValue(for: CBCharacteristic)
            }
        }
        var peripheralName: String!
        
        if let name = advertisementData[CBAdvertisementDataLocalNameKey] as? String {
            peripheralName = name
        }
        else {
            peripheralName = "Unknown"
        }
        let newPeripheral = Peripheral(id: peripherals.count, name: peripheralName, rssi: RSSI.intValue)
        print(newPeripheral)
        peripherals.append(newPeripheral)
    }
    */
    /*
    func startScanning(){
        print("startScanning")
        myCentral.scanForPeripherals(withServices: [nanoServiceCBUUID])
    }
    */
    /*
    func stopScanning(){
        nanoPeripheral = peripheral
        print("stopScanning")
        myCentral.stopScan()
    }
    
    func connectBLE(){
        print("connecting to Nano33BLE")
        //myCentral.connect(<#T##peripheral: CBPeripheral##CBPeripheral#>, options: <#T##[String : Any]?#>)()
    }
    */
}
