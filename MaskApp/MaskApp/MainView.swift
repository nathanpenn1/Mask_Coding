//
//  MainView.swift
//  MaskApp
//
//  Created by David Nikiforov on 3/30/21.
//

import SwiftUI

struct MainView: View {
    @ObservedObject var bleManager = BLEManager()
    @State var selectedIndex = 0
    let tabBarImageNames = ["house.fill", "battery.100.bolt", "line.diagonal"]
    var body: some View {
        VStack {
            ZStack {
                switch selectedIndex {
                case 0:
                    HomeView(bleManager: self.bleManager)
                case 1:
                    BatteryView(bleManager: self.bleManager)
                case 2:
                    GraphView(bleManager: self.bleManager)
                default:
                    Text("Remaining Tabs")
                }
            }
            
            Spacer()
            
            HStack {
                ForEach(0..<3) { num in
                    Button(action: {
                        selectedIndex = num
                    }, label: {
                        Spacer()
                        Image(systemName: tabBarImageNames[num])
                            .font(.system(size: 30, weight: .bold))
                            .foregroundColor(selectedIndex == num ? Color("TabBarColor") : .gray)
                        Spacer()
                    })
                }
            }
            .background(Color("BatteryBackground"))
            //.frame(maxWidth: .infinity, maxHeight: 20,alignment: .center)
        }
        
        
//        TabView{
//            VStack () {
//                Text("UV Mask")
//                    .font(.system(size: 70))
//                    .frame(maxWidth: .infinity, maxHeight: 200, alignment: .center)
//                    .foregroundColor(.red)
//                    .offset(y: -170)
//                Text(bleManager.percentageVal.description + "%\t")
//                    .font(.system(size: 40))
//                    .frame(maxWidth: .infinity, maxHeight: 100,alignment: .center)
//                    .foregroundColor(.red)
//                    .offset(y: -100)
//                
//                HStack () {
//                    Text("UV Light")
//                        .font(.system(size: 20))
//                        .frame(maxWidth: .infinity, alignment: .center)
//                        .foregroundColor(.green)
//                    Text("Charger")
//                        .font(.system(size: 20))
//                        .frame(maxWidth: .infinity, alignment: .center)
//                        .foregroundColor(.green)
//                }
//                .offset(y: -70)
//                
//                HStack() {
//                    Spacer(minLength: 50)
//                    
//                    Text("ON")
//                        .font(.system(size: 40))
//                        .frame(minWidth: 80, minHeight: 60,alignment: .center)
//                        .foregroundColor(.white)
//                        .background(Color.green)
//                        .cornerRadius(10)
//                    
//                    Spacer(minLength: 115)
//                    
//                    Text("ON")
//                        .font(.system(size: 40))
//                        .frame(minWidth: 80, minHeight: 60,alignment: .center)
//                        .foregroundColor(.white)
//                        .background(Color.green)
//                        .cornerRadius(10)
//                    
//                    Spacer()
//                }
//                .offset(y: -65)
//                
//                HStack (spacing: 120) {
//                    NavigationLink(destination: BatteryView()){
//                        Image("BatteryIcon")
//                            .accentColor(Color(.label))
//                    }
//                    NavigationLink(destination:GraphView()){
//                        Image("GraphIcon")
//                            .accentColor(Color(.label))
//
//                    }
//                }
//                .offset(y: -70)
//                if bleManager.isSwitchedOn {
//                    Text("Bluetooth is switched on")
//                        .foregroundColor(.green)
//                }
//                else {
//                    Text("Bluetooth is NOT switched on")
//                        .foregroundColor(.red)
//                }
//                
//            }
//            MainView()
//                .tabItem{
//                    Label("Home", systemImage: "house.fill")
//                }
//            GraphView()
//                .tabItem{
//                    Label("Graph", systemImage: "line.diagonal")
//                }
//            BatteryView()
//                .tabItem{
//                    Label("Battery", systemImage: "battery.100.bolt")
//                }
//        }
    }
}

struct MainView_Previews: PreviewProvider {
    static var previews: some View {
        MainView()
            .preferredColorScheme(.dark)
            
    }
}
