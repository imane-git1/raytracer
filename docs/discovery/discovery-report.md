# Discovery report

## Problem statement

A Los Angeles animation studio needs rendering software that its own team can understand, fix and extend, because a 90-minute film depends on it, but its past tools were either locked by a vendor or became impossible to debug once their authors left.

## Client interview summary

### Why replace the current tools (extensibility and cost)

**Need:** The studio needs to add its own features to its renderer, because the vendor's tool is closed and its licences are very expensive.

> **Q (student):** "You said that you're actually using Maya for rendering. Is there a feature that you need in your new software that you don't have in Maya?"
>

> **A:** "I would say the main thing is the ability to add our own features. With Maya, the problem is the license is very expensive and if we want to add something specific, we have to go through official channels of Maya and either they just say no or it'll take 6 months or a year to add a feature, which means we're limited in our creativity to only what Maya can produce."
 
> **Q (student):** "What did you spend on rendering?"
>
> **A:** "Our licenses. This is why we made a loss. We must have spent over $2 million for all the licenses. Remember the license is seat-based. So normally we pay per machine per artist plus every single node in our render farm we have to pay an individual license, which is why this is a huge budget. We'd like to in-house it, which makes it much more affordable."
 
> **Q (student):** "Do you have a budget for this project?"
>
> **A:** "So we would like to spend no more than 500,000 euro on the project. The last budget was 2 million, so 500,000 represents about one quarter. There will be extra budget for the development team that we will be hiring. But we expect this investment will be cheaper in the long term."
 
**My conclusion:** The studio wants control over its renderer and a lower cost. The 500,000 euro budget is about a quarter of what it spent on licences before.
 
### Scale and schedule
 
**Need:** The studio needs to render a 90-minute HD film at 24 frames per second in at most two months, on a farm of up to 100 machines, with a production version ready on 5 January.
 
> **Q (student):** "How big is the farm?"
>
> **A:** "We have up to 100 machines."
 
> **Q (student):** "What is your deadline to create a movie?"
>
> **A:** "So typically, once the creative side is done, you don't want to spend any more than two months for rendering the final render."
 
> **Q (student):** "And how many pre-renders do you have?"
>
> **A:** "Typically at least 10 different pre-renders per image. So if the average workflow is about 10 pre-renders per image before the final render"
 
> **Q (student):** "What is the size of your project? Is it like 4K? Is it 10 minutes, 90 minutes?"
>
> **A:** "It's a 90 minute feature film at HD."
 
> **Q (student):** "Did you give us a number of frames per second for the rendering? I don't remember if you said it or not."
>
> **A:** "We haven't said, no. We render at 24 frames per second."
>
> **Q (student):** "So 24 frames per second at HD."
>
> **A:** "Yes."
 
> **Q (student):** "When do you need the first [version]?"
>
> **A:** "As I said to your colleague, the production version must be ready for the 5th of January. It must have the full ray tracer capable of producing images for a full film within two month period."
 
**My conclusion:** The numbers give 90 min x 60 s x 24 fps = 129,600 final frames, plus at least 10 pre-renders per image, to be done in two months on at most 100 machines. This is my own calculation, not the client's.
 
### Reliability and debugging
 
**Need:** The studio needs images it can trust (same input, same output) and the ability to find and fix an image anomaly within a day. It needs both a fast, fairly accurate preview and a high quality final image.
 
> **Q (student):** "What will demonstrate that the new [renderer] will fit your needs?"
>
> **A:** "I think there are two elements. One, it produces a reliable image. So if I give it some inputs, I can always expect the same output. And the second one is that if there is an image problem, an anomaly, we can figure out within the same day why there is that anomaly and what steps we can take to correct it. To go back to the problem we had six months ago, we had these black spots and nobody could tell us why. That is the biggest frustration."
 
> **Q (student):** "What is more important, image [quality] or fast image?"
>
> **A:** "For the designer a fast image which is pretty accurate is very important. The designer, we don't want him to wait too long to see what the result of his work is. But in the final scene, a high quality image is very important."
 
**My conclusion:** Reliability and being able to explain a defect are the client's success criteria. Speed and quality both matter, but the client gave no trade-off between them.
 
### Maintainability and the departure of developers
 
**Need:** The studio needs software that its own team can maintain in the long term, including when the person who wrote it leaves.
 
> **Q (student):** "Who will maintain it, what skill will they have, let's say in 5 years afterwards?"
>
> **A:** "So we would like to maintain the solution in-house and we would like to be able to maintain it in the long term. So it must be a solution that is maintainable."
 
> **Q (student):** "Is there any information that we need but we didn't ask?"
>
> **A:** "So, there's one question that maybe we all forgot about, is what happens when the person who wrote it leaves the team. And this is something that really bit us last time, the person who wrote the software had left our team already and we found these artifacts and no one could tell me why."
 
> **Q (student):** "In fact there's two scenarios: you provide the initial product and then you leave, now we need to maintain it, are we able to maintain it without you? Second question is, if one of my team members leave, can the other team members continue to understand and use this code in the long term?"
>
> **A:** "Yeah. But what happened last time is that we had a team of five people. But the key person who wrote it had left and even the five people, they didn't know how to debug. Nobody could tell me why we had these black spots."
 
**My conclusion:** The client raised this topic itself, which suggests it is the most important one. A team of five could not debug code written by one person, so understanding the code matters as much as the code working.
 
### Open source, partners and documentation
 
**Need:** The studio needs code that partners can use and contribute to, with the final responsibility staying in-house, and documentation for both developers and artists.
 
> **Q (student):** "Do other studios use the same programming language?"
>
> **A:** "Yes."
>
> **A (client, continuing):** "I don't want to give up information voluntarily but we do rely on partners to do the rendering for us. And these partners have skill sets to contribute to this project as well, which means they will be using the software and probably participating in its lifetime."
 
> **Q (student):** "How will contributions be handled and who will review the contribution?"
>
> **A:** "We will maintain the responsibility in-house but we would like a way for them to contribute, correct bugs, propose changes."
 
> **Q (student):** "Do you have rules or a style for the code?"
>
> **A:** "Not especially, no. We rely on you students for that."
 
> **Q (student):** "About open sourcing, will all the code be open source, or do you need some part to be in-house to have control about the software?"
>
> **A:** "Currently all be open source."
 
> **Q (student):** "Do you need documentation?"
>
> **A:** "No, you provide that."
 
> **Q (student):** "Who will read the documentation, is it technical?"
>
> **A:** "We do have a development team which will take ownership of what you make for us. So there'll be technical people reading it. However, we expect some kind of user guide for the graphic artists or the people setting up the render file on how to use it."
 
**My conclusion:** Partners will both use and contribute to the code, so the project needs to be easy to read and to contribute to. The client sets no code style, so the team must choose and document its own.
 
### Scope of the software
 
**Need:** The studio needs a rendering-only "black box" that reads a scene file and writes images, with no interface, starting with ray tracing of primitive shapes and able to grow.
 
> **Q (student):** "Can it read a file? Do you need an interface for it?"
>
> **A:** "No. Typically what happens is that a standard file will be created, saved by the designer and this file will be put onto the render farm and just processes launched to render the image. So no interface is required."
 
> **Q (student):** "How will the designer receive the images and who approves the rendering?"
>
> **A:** "So the designer will use some third party software to position the scene. So put objects in the scene and set up lighting typically. Then they'll save a file and that file will be the input to your ray tracer to render a final image. These images will just be saved to disk and then sequenced into a film or we can consult one by one."
 
> **Q (student):** "What kind of content do you render, like full animation or live action effects?"
>
> **A:** "It's mainly full animation and I'd say the most similar is Toy Story."
 
> **Q (student):** "Do you want software to render frames or to create frames? 3D software?"
>
> **A:** "No, we just want to render. So, it's a black box that takes a description of a scene and outputs an image."
 
> **Q (student):** "Which technique do you use?"
>
> **A:** "For the moment we're just going to start off with the ray tracing, just ray tracing for the moment, that's the most urgent for our next project, but we would like the software to be able to include new effects, new shapes."
 
> **Q (student):** "what you want is only primitive objects?"
>
> **A:** "Yes."
 
> **Q (student):** "The ray tracer must support a specific format?"
>
> **A:** "I let you decide that but it must be a standardized format that we can use and our partners."
 
> **Q (student):** "You don't want an extension to import your own models?"
>
> **A:** "Ah, perhaps that would be very useful."
>
> **Q (student):** "So do you want primitive objects or your own models?"
>
> **A:** "That all sounds great."
 
> **Q (student):** "Which extension do you use?"
>
> **A:** "Whatever is that extension the current software can support."
>
> **Q (student):** "But you don't have an extension that you use?"
>
> **A:** "I will have to ask my graphics team to see what they use."
 
> **Q (student):** "Do you have an example to show us?"
>
> **A:** "Well, the example was in my original brief."
 
**My conclusion:** The software has one job: read a scene file, produce images. Everything else (editing scenes, a user interface) is outside the scope. Which file format to use is left to us, as long as it is standard.
 

### Open questions

- - "10 pre-renders per image": is this 10 extra renders before each final image? The answer was cut off in the recording.
- The exact resolution behind "HD" was not given.
- Which standard file format the graphics team uses today is unknown: the client has to ask them.
- "Currently all be open source" is unclear in the recording: is every part of the code open source?
- The client said a development team "will take ownership" of the software and also that it "will be hiring" one. Is it an existing team or a new one, and how large?
- The client wants both a fast preview and a high quality final image, but gave no priority between them.
- How a new developer learns the code, how the client tests a renderer today, and whether the team uses AI to write code were not asked.

## State of the art

| Solution     | Maker                         | Licence                              | Pricing (date checked)                                                                                         | Capabilities                                                                                                      | Sources                                                      |
|--------------|-------------------------------|--------------------------------------|---------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------|
| Maya + Arnold | Autodesk                     | Proprietary, subscription            | Not published on the page read (prices did not display), checked 2026-11-16. TODO: check on autodesk.com      | 3D animation, modelling, simulation and rendering; Arnold included in the Media & Entertainment Collection       | https://www.autodesk.com/collections/media-entertainment     |
| RenderMan    | Pixar                         | Proprietary commercial; free for non-commercial use | 595 USD per licence (includes Tractor), 250 USD/year maintenance per licence, checked 2026-11-16. Render node price not listed: contact sales | Production renderer; Tractor is Pixar's render farm manager | https://renderman.pixar.com/store/                           |
| Cycles       | Blender project (Cycles Developers) | Apache License 2.0 (open source) | No price on the page read; source code is free to use, checked 2026-11-16                                    | Physically based production renderer                                                                                | https://cycles-renderer.org/                                 |
| V-Ray        | Chaos                         | Proprietary, subscription            | Not published on the page read; contact sales for more than 10 licences, checked 2026-11-16                  | Production renderer; render node licences exist                                                                     | https://www.chaos.com/pricing                                |

## What is ray tracing?

Ray tracing is a computer graphics technique used to replicate the behavior of light within a 3D scene. It involves simulating the path of light rays from the camera toward objects and light sources in order to calculate lighting effects, shadows, and reflections. This technique is primarily used to achieve more realistic imagery in computer generated graphics.

**Sources:** : Wikipedia – Ray Tracing: https://fr.wikipedia.org/wiki/Ray_tracing

## What is C++?

### Programming paradigms

C++ is a multi-paradigm programming language, meaning it allows for various approaches to programming. It supports, among others, procedural programming which involves organizing code into functions—object-oriented programming based on classes and objects and generic programming, which enables the creation of reusable code through templates. These different approaches can be combined within a single project.

### What to watch out for

Using C++ requires a certain level of care, particularly regarding memory management, pointers, and references. Improper use of these elements can lead to errors or operational issues. One must also pay close attention to syntax, compilation, and the program's compatibility across different platforms. It is therefore important to write well-structured code and to favor tools from the standard library in order to avoid certain types of errors.

### Shaping the domain model

In C++, it is possible to represent the various elements of a domain using classes and structures. Classes allow for the grouping of data and functionality related to a specific element, while structures are primarily used to organize data that are logically connected. This organization makes the code clearer, better structured, and easier to maintain. It is therefore important to accurately identify the elements of the domain and their relationships before representing them within the program.

**Sources:** : 
- Coddy – What Is C++? (Statically Typed and Multi-Paradigm): https://coddy.tech/docs/fr/cpp/what-is-cpp#typage-statique-et-multiparadigme
- C++ Core Guidelines – Classes and Class Hierarchies: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-class