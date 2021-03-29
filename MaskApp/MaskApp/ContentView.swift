//
//  ContentView.swift
//  MaskApp
//
//  Created by David Nikiforov on 2/12/21.
//
import SwiftUI
import SwiftUICharts
import Charts

struct ContentView: View {
    @ObservedObject var bleManager = BLEManager()
    var body: some View {
        NavigationView {
            VStack () {
                Text("UV Mask")
                    .font(.system(size: 70))
                    .frame(maxWidth: .infinity, maxHeight: 200, alignment: .center)
                    .foregroundColor(.red)
                    .offset(y: -170)
                Text(bleManager.percentageVal.description + "%\t")
                    .font(.system(size: 40))
                    .frame(maxWidth: .infinity, maxHeight: 100,alignment: .center)
                    .foregroundColor(.red)
                    .offset(y: -100)
                
                HStack () {
                    Text("UV Light")
                        .font(.system(size: 20))
                        .frame(maxWidth: .infinity, alignment: .center)
                        .foregroundColor(.green)
                    Text("Charger")
                        .font(.system(size: 20))
                        .frame(maxWidth: .infinity, alignment: .center)
                        .foregroundColor(.green)
                }
                .offset(y: -70)
                
                HStack() {
                    Spacer(minLength: 50)
                    
                    Text("ON")
                        .font(.system(size: 40))
                        .frame(minWidth: 80, minHeight: 60,alignment: .center)
                        .foregroundColor(.white)
                        .background(Color.green)
                        .cornerRadius(10)
                    
                    Spacer(minLength: 115)
                    
                    Text("ON")
                        .font(.system(size: 40))
                        .frame(minWidth: 80, minHeight: 60,alignment: .center)
                        .foregroundColor(.white)
                        .background(Color.green)
                        .cornerRadius(10)
                    
                    Spacer()
                }
                .offset(y: -65)
                
                HStack (spacing: 120) {
                    NavigationLink(destination: BatteryView()){
                        Image("BatteryIcon")
                            .accentColor(Color(.label))
                    }
                    NavigationLink(destination: UVIntesityView(bleManager1: bleManager)){
                        Image("GraphIcon")
                            .accentColor(Color(.label))
                        
                    }
                }
                .offset(y: -70)
                //LineView(data: bleManager.yVal , title: "UV Intesity", legend: "(nm)")
                //LineChartView(data: bleManager.yVal, title: "UV Intesity")
                
                if bleManager.isSwitchedOn {
                    Text("Bluetooth is switched on")
                        .foregroundColor(.green)
                }
                else {
                    Text("Bluetooth is NOT switched on")
                        .foregroundColor(.red)
                }
            }
        }
    }
}

struct BatteryView: View {
    //@ObservedObject var bleManager = BLEManager()
    var body: some View {
        VStack() {
            HStack () {
                Text("V(capacity)")
                    .font(.system(size: 20))
                    .frame(maxWidth: .infinity, alignment: .center)
                    .foregroundColor(.green)
                Text("V(battery)")
                    .font(.system(size: 20))
                    .frame(maxWidth: .infinity, alignment: .center)
                    .foregroundColor(.green)
            }
            .offset(y: -200)
            
            HStack() {
                Spacer()
                
                Text("6V")
                    .font(.system(size: 40))
                    .frame(minWidth: 80, minHeight: 60,alignment: .center)
                    .foregroundColor(.white)
                    .background(Color.green)
                    .cornerRadius(10)
                
                Spacer(minLength: 115)
                
                Text("5V")
                    .font(.system(size: 40))
                    .frame(minWidth: 80, minHeight: 60,alignment: .center)
                    .foregroundColor(.white)
                    .background(Color.green)
                    .cornerRadius(10)
                
                Spacer()
            }
            .offset(y: -200)
            
            Text("Perecentage")
                .font(.system(size: 20))
                .frame(maxWidth: .infinity, alignment: .center)
                .foregroundColor(.green)
                .offset(y: -150)
            
            Text("83.33%")
                .font(.system(size: 40))
                .frame(minWidth: 80, minHeight: 60,alignment: .center)
                .foregroundColor(.white)
                .background(Color.green)
                .cornerRadius(10)
                .offset(y: -150)
            
            Text("Charging ON")
                .font(.system(size: 45))
                .frame(maxWidth: .infinity, alignment: .center)
                .foregroundColor(.red)
                .offset(y: -50)
        }
    }
}

struct UVIntesityView: View {
    @ObservedObject var bleManager1 : BLEManager
    var body: some View {
        HStack() {
            LineView(data: bleManager1.yVal , title: "UV Intesity", legend: "(nm)")
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            .preferredColorScheme(.light)
    }
}
