//
//  ContentView.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-15.
//

import SwiftUI

struct ContentView: View {
    @Binding var document: URMapDocument

    var body: some View {
        NavigationView {
            explorer
            HStack {
                editor
                inspector
            }
        }
    }
    
    var explorer: some View {
        TabView {
            tileTypeExplorer.tabItem { Text("Tiles") }
            layerExplorer.tabItem { Text("Layers") }
        }
        
    }
    
    var tileTypeExplorer: some View {
        List {
            Text("Tile type 2")
            Text("Tile type 2")
        }
    }
    
    var layerExplorer: some View {
        List {
            Text("Layer A")
            Text("Layer B")
            Text("Layer C")
        }
    }
    
    var editor: some View {
        VStack {
            Text("Map size: \(document.state.width)x\(document.state.height)")
            Image("tiles", bundle: .main)
        }
            .frame(maxWidth: .infinity, maxHeight: .infinity)
    }
    
    var inspector: some View {
        VStack {
            Text("Inspector Panel")
        }.frame(width: 300)
    }
}

#Preview {
    ContentView(document: .constant(URMapDocument()))
}
