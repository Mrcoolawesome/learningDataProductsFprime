- We need to start implementing the data product manager to give Josh a demo. 
- For some reason when I add a new component it gives me an error saying that certain subdirectorys in the Components file don't exist telling me we've branched off of devel which was bad. 
    - Our current branch is called `data-products`

## What to actually do now
 - I've made a few connections in the DummyComponents, but I think we're gonna have to make a different dummy component because this one needs buffers for some reason.
 - We're using the `dummyI2C` component to be a producer
    - This might be bad becuase this commponent needs buffers for some reason which I don't wanna deal with
    - I might wanna just make a new component or edit this one to run on a rate group and send data upon every rate group tick.
 - We also just really need to figure out how to connect together the fprime made dp components or if we even really need to
    - Bc I'm not really sure what the catelog one does
 - Need to figure out how to make records as well
 - Look in our obsidian notes to see more information about what we've learned
 - I haven't generated the implementation files for the dummy I2C component yet either. 

BIG TODOS:
 - Figure out if we should use `dummyI2C` or edit it to just output dummy data on a rate group, OR we should make a brand new component to do that.
 - Then, we need to figure out how to connect this properly to the built-in components to do stuff.
    - Then, we need to figure out how to properly make the data into records, so that we can put them in containers. 
 - There's a ton of built-in functions that they have to help with all of this (like they have a function to measure the size of a piece of data in C++ so the container knows how much data we're gonna need to allocate), so we should figure out how to use these too I think.
 - It might be helpful to look in the new fprime-4.0 repo to see if there are implementation examples that they have out there. 
 - So, in the end, we should have a dummy component that saves some data (like maybe an F32 number) to storage, and be able to retrieve that data as well. 

 What I'm going to do:
 - Make a new component that outputs information based on me pressing a button in the gds. 
 - This component will send out to the data product thingy to do things
 - I'm also gonna do it on v4 of fprime becauase they have the premade dataproduct subtopology allegedly 

 What I should do when I get back:
  - Hookup everything in the topology, and then figure out how the heck this is written in a producer component

Next things to do:
 - I kinda got an understanding of how to use `productRequestOut_out` and it's in the cpp file, i still need to figure some things out, but we need to continue writing stuff, (you should guess the names of the functions like productRequestOut and then build in the component folder and it'll suggest the right function probably). if we just do this for the rest of the stuff we should be fine.
 - I'm not sure how it's gonna get the data (`silly_data`) from the send data command handler, so we need to get that figured out.