//
//  AGM+mapSize.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-16.
//

import Foundation

extension AGM {
    var mapSize: MapSize {
        return .init(width: Int(width), height: Int(height))
    }
    
    struct MapSize {
        var width: Int
        var height: Int
    }
}
