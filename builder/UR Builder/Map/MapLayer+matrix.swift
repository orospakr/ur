//
//  MapLayer+matrix.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-16.
//

import Foundation

extension MapLayer {
    /// Return the tiletype index for a given tile coordinate. Width is the stride, in row major-order.
    func getTileAt(width: Int, x: Int, y: Int) -> Int {
        let index = (x * width) + y
        return Int(self.tiles[index])
    }
}
