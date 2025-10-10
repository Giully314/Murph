// PURPOSE: Define the low level renderer api.
//
// CLASSES:
//  PrimitiveRenderer: define low level render api.
//
// DESCRIPTION:
//  This module defines the low level api (line, tringle, ...) on a Context data.
//
// USAGE:
//
//


export module murph.canvas.renderer;

import murph.types;
import murph.canvas.context;

namespace murph::canvas {

// This class implements the low level primitives to draw pixels on a buffer.
// The Context data must be always non null and it is responsability of the caller to
// ensure this precondition.
export class PrimitiverRenderer {
public:
    explicit PrimitiverRenderer(non_null_ptr<Context> context_) {}
    
    
    
    

private:
    non_null_ptr<Context> context;
};
    
} // namespace murph::canvas 
