#!/bin/bash

# Usage:
# file-event-watch command-to-run path1 [path2, ...]
# TODO: Add fswatch event option to enable/disable different event types

cmd=$1
shift
files=$@
$cmd && fswatch -0 $files | {
  while read -d "" event; do
    # case $event in
			echo $event
      # *Created|*Updated|*Removed|*Renamed|*OwnerModified|*AttributeModified|*MovedFrom|*MovedTo )
        # # https://github.com/emcrisostomo/fswatch/blob/master/src/fswatch.cpp
        # # If it's one of these events, run cmd, else ignore it
        # $cmd
        # ;;
    # esac
  done
}
