/*

    1. Load config

    2. Create interposer

    3. Create basedie

    4. Add topdie to basedie (_name, _pins_map)

    5. Add topdieinst to basedie (_name, _topdie, _tob, _nets is empty now)

    6. Create Net

        for each sync in config.connections

        - if sync == -1 => create net to basedie
        - else, all net has the same sync will see as one sync net
            so, create sync, and add each net into it

        > basedie owns nets, topdieinst borrows nets 

*/