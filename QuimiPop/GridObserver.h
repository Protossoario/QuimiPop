//
//  GridObserver.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/4/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef __QuimiPop__GridObserver__
#define __QuimiPop__GridObserver__

class GridObserver {
public:
    virtual void formedMoleculeRow(int row, int col, int size) = 0;
    virtual void formedMoleculeCol(int row, int col, int size) = 0;
};

#endif /* defined(__QuimiPop__GridObserver__) */
