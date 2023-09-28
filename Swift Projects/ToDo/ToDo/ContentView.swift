//
//  ContentView.swift
//  ToDo
//
//  Created by Akshaj Kanumuri on 9/27/23.
//

import SwiftUI

enum CalcButton {
    
}

struct ContentView: View {
    var body: some View {
        ZStack {
            Color.black.edgesIgnoringSafeArea(.all)
            
            VStack {
                // Display Text
                HStack{
                    Spacer()
                    Text("0")
                        .bold()
                        .font(.system(size: 64))
                        .foregroundColor(.white)
                }
                .padding()
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
