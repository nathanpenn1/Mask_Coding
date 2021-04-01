//
//  HomeView.swift
//  MaskApp
//
//  Created by David Nikiforov on 3/30/21.
//

import SwiftUI

struct HomeView: View {
    @ObservedObject var bleManager: BLEManager
    var body: some View {
        NavigationView {
            ZStack {
                Color("BatteryBackground")
                    .edgesIgnoringSafeArea(.all)
                VStack {
                    
                    Spacer()
                    VStack {
                        Text("A BETTER BREATH")
                            .font(.system(size: 30))
                            .frame(maxWidth: .infinity, maxHeight: 50, alignment: .center)
                            .foregroundColor(Color("HomeBoxText"))
                        
                        Text("WITH UV TECHNOLOGY")
                            .font(.system(size: 30))
                            .frame(maxWidth: .infinity, maxHeight: 50, alignment: .center)
                            .foregroundColor(Color("HomeBoxText"))
                        
                        Text("EST. 2020")
                            .font(.system(size: 25))
                            .frame(maxWidth: .infinity, maxHeight: 50, alignment: .center)
                            .foregroundColor(Color("HomeBoxText"))
                    }
                    .offset(y: -80)
                    Spacer()
                    
                    HStack() {
                        
                        Spacer()
                        
                        ZStack {
                            Rectangle()
                                .frame(width:120, height: 100)
                                .foregroundColor(Color("HomeBox"))
                                .cornerRadius(10)
                                .shadow(color: Color("BatteryShadow"), radius: 5, x: 0, y: 0)
                            
                            Text("UV LIGHT")
                                .font(Font.custom("Helvetica-Neue", size: 20))
                                .foregroundColor(Color("HomeBoxText"))
                                .bold()
                                .offset(y: -25)
                            
                            Text("ON")
                                .font(Font.custom("Helvetica-Neue", size: 45))
                                .foregroundColor(Color("ON"))
                                .bold()
                                .offset(y: 10)
                        }
                        
                        Spacer()
                        
                        ZStack {
                            Rectangle()
                                .frame(width:120, height: 100)
                                .foregroundColor(Color("HomeBox"))
                                .cornerRadius(10)
                                .shadow(color: Color("BatteryShadow"), radius: 5, x: 0, y: 0)
                            
                            Text("Charger")
                                .font(Font.custom("Helvetica-Neue", size: 20))
                                .foregroundColor(Color("HomeBoxText"))
                                .bold()
                                .offset(y: -25)
                            
                            Text("OFF")
                                .font(Font.custom("Helvetica-Neue", size: 45))
                                .foregroundColor(Color("OFF"))
                                .bold()
                                .offset(y: 10)
                        }
                        
                        Spacer()
                    }.offset(y: -30)
                    
    //                if bleManager.isSwitchedOn {
    //                    Text("Bluetooth is switched on")
    //                        .foregroundColor(.green)
    //                }
    //                else {
    //                    Text("Bluetooth is NOT switched on")
    //                        .foregroundColor(.red)
    //                }
                    
                    Spacer()
                    
                }
            }
        }
    }
}
struct HomeView_Previews: PreviewProvider {
    static var previews: some View {
        HomeView(bleManager: BLEManager())
            .preferredColorScheme(.dark)
    }
}
