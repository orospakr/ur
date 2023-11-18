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
            ForEach(Array(document.state.tileTypes.enumerated()), id: \.offset) { _, tileType in
                HStack {
                    Image(nsImage: document.tileset.tiles[Int(tileType.graphicIndex)].previewImage)
                    Text(tileType.title)
                }
            }
        }
    }
    
    var layerExplorer: some View {
        List {
            ForEach(Array(document.state.layers.enumerated()), id: \.offset) { idx, layer in
                HStack {
                    Text("Layer \(idx + 1)")
                }
            }
        }
    }
    
    var editor: some View {
        VStack {
            Text("Map size: \(document.state.width)x\(document.state.height)")
            MapCanvas(tileTypes: document.state.tileTypes, mapSize: document.state.mapSize, mapLayer: document.state.layers.first ?? MapLayer(), tileset: document.tileset)
        }
            .frame(maxWidth: .infinity, maxHeight: .infinity)
    }
    
    var inspector: some View {
        VStack {
            Text("Inspector Panel")
        }.frame(width: 300)
    }
}

struct MapCanvas: View {
    let tileTypes: [TileType]
    let mapSize: AGM.MapSize
    let mapLayer: MapLayer
    let tileset: Tileset
    
    
    let scaleFactor = 1
    
    let tileSize = 32
    
    var body: some View {
        Canvas { context, size in
            
            (0..<mapSize.width).forEach { x in
                (0..<mapSize.height).forEach { y in
                    let tileIndex = mapLayer.getTileAt(width: mapSize.width, x: x, y: y)
                    
                    context.draw(Image(tileset.tiles[tileIndex].firstFrame, scale: 1.0, label: Text("tile")), in: CGRect.init(origin: .init(x: x * tileSize * scaleFactor, y: y * tileSize * scaleFactor), size: CGSize(width: tileSize * scaleFactor, height: tileSize * scaleFactor)), style: FillStyle(eoFill: false, antialiased: false))
                }
            }
            
//            context.draw(Image(tileset.tiles[3].firstFrame, scale: 1.0, label: Text("tile")), in: CGRect.init(origin: .zero, size: CGSize(width: 128, height: 128)), style: FillStyle(eoFill: false, antialiased: false))
        }
    }
}

#Preview {
    ContentView(document: .constant(URMapDocument()))
}
