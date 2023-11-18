//
//  CanvasView.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-18.
//

import Foundation
import SwiftUI


struct CanvasView: View {
    let tileTypes: [TileType]
    let mapSize: AGM.MapSize
    @ObservedObject var editorState: EditorState
    
    let tileset: Tileset
    
    @Binding var mapLayers: [MapLayer]
    
    private let scaleFactor = 1
    
    private let tileSize = 32
    
    @State private var reticleLocation: (Int, Int)? = nil
    
    var body: some View {
        Canvas { context, size in
            
            (0..<mapSize.width).forEach { x in
                (0..<mapSize.height).forEach { y in
                    
                    mapLayers.enumerated().forEach { layerIdx, mapLayer in
                        if(!editorState.disabledLayers.contains(layerIdx)) {
                            let tileIndex = mapLayer.getTileAt(width: mapSize.width, x: x, y: y)
                            
                            context.draw(Image(tileset.tiles[tileIndex].firstFrame, scale: 1.0, label: Text("tile")), in: CGRect.init(origin: .init(x: x * tileSize * scaleFactor, y: y * tileSize * scaleFactor), size: CGSize(width: tileSize * scaleFactor, height: tileSize * scaleFactor)), style: FillStyle(eoFill: false, antialiased: false))
                        }
                    }
                    
                }
            }
            
            if let reticleLocation = self.reticleLocation {
                context.stroke(Path(CGRect(x: tileSize * reticleLocation.0, y: tileSize * reticleLocation.1, width: tileSize, height: tileSize)), with: .color(.red), lineWidth: 2)
            }
            
//            context.draw(Image(tileset.tiles[3].firstFrame, scale: 1.0, label: Text("tile")), in: CGRect.init(origin: .zero, size: CGSize(width: 128, height: 128)), style: FillStyle(eoFill: false, antialiased: false))
        }.frame(width: CGFloat(mapSize.width * tileSize), height: CGFloat(mapSize.height * tileSize))
            .onContinuousHover(coordinateSpace: .local) { hoverPhase in
                switch(hoverPhase) {
                case .active(let location):
                    reticleLocation = (Int(location.x) / tileSize, Int(location.y) / tileSize)
                case .ended:
                    reticleLocation = nil
                }
            }
    }
}
