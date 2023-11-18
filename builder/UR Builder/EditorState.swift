//
//  EditorState.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-18.
//

import Foundation

class EditorState: ObservableObject {
    /// Currently selected layer to interact with (identified by index).
    @Published var activeLayer: Int? = nil
    
    /// Layers currently disabled from rendering
    @Published var disabledLayers: Set<Int> = []
    
    /// Currently selected tile type
    @Published var activeTileType: Int? = nil
}
