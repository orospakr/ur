//
//  AGM+legacyImport.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-17.
//

import Foundation

extension AGM {
    /// Load a legacy CSV format map from a directory.
    static func loadLegacyCSVFormat(directory: URL) throws -> AGM {
        // check if layerA.agm is present in the directory:
        let layerAUrl = directory.appendingPathComponent("layerA.agm")
        guard FileManager.default.fileExists(atPath: layerAUrl.path) else {
            throw ImportError(message: "The file layerA.agm was not found in the selected folder.")
        }

        let importedLayers = try ["layerA", "layerB", "layerC"].map { layerName in
            let layerUrl = directory.appendingPathComponent("\(layerName).agm")
            guard FileManager.default.fileExists(atPath: layerUrl.path) else {
                throw ImportError(message: "The file \(layerName).agm was not found in the selected folder.")
            }
            let layerData = try Data(contentsOf: layerUrl)

            return try loadLayerFromCSVBuffer(layerData)
        }

        var agm = AGM.blank

        agm.layers = importedLayers
        return agm
    }


    private static func loadLayerFromCSVBuffer(_ csvBuffer: Data) throws -> MapLayer {
    

        // load agm csv fil
        
        let layerString = String(data: csvBuffer, encoding: .utf8)!

        // parse csv file:
        let layerRows = layerString.split(separator: "\n")
        let layerDataRows = layerRows.map { row in
            row.split(separator: ",").map { cell in
                // minus-1 because I 1-indexed the original format
                Int32(cell)! - 1
            }
        }


        var layer = MapLayer()
        layer.tiles = layerDataRows.flatMap { row in
            row
        }
        return layer
    }


    struct ImportError: LocalizedError, Error {
        var message: String

        var errorDescription: String? {
            return message
        }
    }
}
