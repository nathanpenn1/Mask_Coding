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
                    
                    GeometryReader { geo in
                        Image("BlackImage")
                            .resizable()
                            .aspectRatio(contentMode: .fit)
                            .frame(width: geo.size.width)
                    }
                    .offset(y: -60)
                    
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
                    }.offset(y: -100)
                    
                    Spacer()
                    
                    VStack {
                        Button(action: {
                            if(bleManager.buttonOnOff == 0) {
                                print("1")
                                bleManager.buttonOnOff = 1
                                bleManager.write(value: Data([UInt8(1)]) , characteristic: bleManager.button!)
                            }
                            else {
                                print("0")
                                bleManager.buttonOnOff = 0
                                bleManager.write(value: Data([UInt8(0)]) , characteristic: bleManager.button!)
                            }
                        }) {
                            Image(systemName: "power")
                                .padding(10)
                                .font(.system(size: 40, weight: .bold))
                                .foregroundColor((bleManager.strOut != "Ready!") ? Color.gray : Color.white)
                                .background(Color("ButtonOnOffBackground"))
                                .clipShape(/*@START_MENU_TOKEN@*/Circle()/*@END_MENU_TOKEN@*/)
                                
                        }
                        //.frame(width: 100, height: 100)
                        .offset(y: -60)
                        .disabled(bleManager.strOut != "Ready!")
                    }
                    Spacer()
                }
            }
        }
    }
}
struct HomeView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            HomeView(bleManager: BLEManager())
                .previewDevice(/*@START_MENU_TOKEN@*/"iPhone 11"/*@END_MENU_TOKEN@*/)
                .preferredColorScheme(.dark)
        }
    }
}
