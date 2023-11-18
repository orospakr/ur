//
//  ContentView.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-15.
//

import SwiftUI
import os.log

struct ContentView: View {
    @Binding var document: URMapDocument
    @StateObject var editorState: EditorState = EditorState()
    
    var body: some View {
        NavigationView {
            explorer
            HStack {
                canvas
                inspector
            }
        }
    }
    
    var explorer: some View {
        ExplorerView(tileset: document.tileset, editorState: self.editorState, tileTypes: $document.state.tileTypes, layers: $document.state.layers)
    }
    
    var canvas: some View {
        VStack {
            Text("Map size: \(document.state.width)x\(document.state.height)")
            ScrollView([.horizontal, .vertical]) {
                CanvasView(tileTypes: document.state.tileTypes, mapSize: document.state.mapSize, editorState: self.editorState, tileset: document.tileset, mapLayers: $document.state.layers)
            }
        }
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
