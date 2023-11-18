//
//  UR_BuilderDocument.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-15.
//

import SwiftUI
import UniformTypeIdentifiers
import os.log

extension UTType {
    static var urMap: UTType {
        UTType(exportedAs: "ca.orospakr.ur.map")
    }
}

struct URMapDocument: FileDocument {
    var state: AGM
    
    // right now hard coded in the app, so technically abusing the Document class to do injection lol
    var tileset: Tileset = Tileset()

    init(state: AGM = AGM.blank) {
        self.state = state
    }

    static var readableContentTypes: [UTType] { [.urMap] }

    init(configuration: ReadConfiguration) throws {
        var tt = TileType()
        tt.solid = true

        var agm: AGM
        
        guard let data = configuration.file.regularFileContents
        else {
            throw CocoaError(.fileReadCorruptFile)
        }
        
        do {
            agm = try AGM(serializedData: data)
        } catch {
            os_log("Cannot decode, because: %@", error.localizedDescription)
            throw CocoaError(.fileReadCorruptFile)
        }

        self.state = agm
    }
    
    func fileWrapper(configuration: WriteConfiguration) throws -> FileWrapper {
        let data = try state.serializedData()
        return .init(regularFileWithContents: data)
    }
}
