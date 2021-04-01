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
        ZStack {
            Color("BatteryBackground")
                .edgesIgnoringSafeArea(.all)
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
                .frame(maxWidth: .infinity, maxHeight: 50,alignment: .center)
            }
        }
    }
}

struct MainView_Previews: PreviewProvider {
    static var previews: some View {
        MainView()
            .preferredColorScheme(.dark)
            
    }
}
