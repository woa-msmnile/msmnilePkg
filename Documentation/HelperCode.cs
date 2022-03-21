string GetDefineForEfiMemType(string type)
{
    switch (type)
    {
        case "Reserv":
            {
                return "EfiReservedMemoryType";
            }
        case "BsData":
            {
                return "EfiBootServicesData";
            }
        case "Conv":
            {
                return "EfiConventionalMemory";
            }
        case "RtData":
            {
                return "EfiRuntimeServicesData";
            }
        case "MmIO":
            {
                return "EfiMemoryMappedIO";
            }
        default:
            {
                throw new Exception();
            }
    }
}

string GetDefineForResourceAttribute(string type)
{
    switch (type)
    {
        case "SYS_MEM_CAP":
            {
                return "SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES";
            }
        case "WRITE_COMBINEABLE":
            {
                return "EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE";
            }
        case "INITIALIZED":
            {
                return "EFI_RESOURCE_ATTRIBUTE_INITIALIZED";
            }
        case "UNCACHEABLE":
            {
                return "EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE";
            }
        default:
            {
                throw new Exception();
            }
    }
}

string GetDefineForResourceType(string type)
{
    switch (type)
    {
        case "SYS_MEM":
            {
                return "EFI_RESOURCE_SYSTEM_MEMORY";
            }
        case "MEM_RES":
            {
                return "EFI_RESOURCE_MEMORY_RESERVED";
            }
        case "MMAP_IO":
            {
                return "EFI_RESOURCE_MEMORY_MAPPED_IO";
            }
        default:
            {
                throw new Exception();
            }
    }
}

string GetDefineForCacheAttribute(string type)
{
    switch (type)
    {
        case "WRITE_BACK_XN":
            {
                return "ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK";
            }
        case "UNCACHED_UNBUFFERED_XN":
            {
                return "ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED";
            }
        case "UNCACHED_UNBUFFERED":
            {
                return "ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED";
            }
        case "WRITE_THROUGH_XN":
            {
                return "ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH";
            }
        case "WRITE_BACK":
            {
                return "ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK";
            }
        case "NS_DEVICE":
            {
                return "ARM_MEMORY_REGION_ATTRIBUTE_DEVICE";
            }
        default:
            {
                throw new Exception();
            }
    }
}

void PrintMemMapInUnderstandableFormat(string filePath)
{
    string[] lines = File.ReadAllLines(filePath);

    bool ok = false;

    foreach (string line in lines)
    {
        if (!ok)
        {
            ok = line == "[MemoryMap]";
            continue;
        }

        if (line.StartsWith("#") || line == "[RegisterMap]" || string.IsNullOrEmpty(line))
        {
            continue;
        }

        if (line == "[ConfigParameters]")
        {
            break;
        }

        var elements = line.Split(",").Select(x => x.Trim()).ToArray();

        if (elements.Count() != 8)
        {
            throw new Exception();
        }

        Console.WriteLine($"\t/* {elements[2].Trim('\"')} */");
        Console.WriteLine("\t{" + $"{elements[0]}, {elements[1]}, {GetDefineForResourceType(elements[4])},\n" +
         $"\t {GetDefineForResourceAttribute(elements[5])}, {GetDefineForCacheAttribute(elements[7])},\n" +
         $"\t {elements[3]}, {GetDefineForEfiMemType(elements[6])}" + "},");
    }
}

void PrintGapsInMemMap(string filePath)
{
    string[] lines = File.ReadAllLines(filePath);

    bool ok = false;

    bool secondok = true;

    var ranges = lines.Select(line =>
    {
        if (!ok)
        {
            ok = line == "[MemoryMap]";
            return (null, null);
        }

        if (line.StartsWith("#") || line == "[RegisterMap]" || string.IsNullOrEmpty(line) || !secondok)
        {
            if (line == "[RegisterMap]")
                secondok = false;
            return (null, null);
        }

        if (line == "[ConfigParameters]")
        {
            return (null, null);
        }

        var elements = line.Split(",").Select(x => x.Trim()).ToArray();

        if (elements.Count() != 8)
        {
            return (null, null);
        }

        return (elements[0], elements[1]);
    }).Where(x => x.Item1 != null).OrderBy(x => Convert.ToInt64(x.Item1.Replace("0x", ""), 16)).ToArray();

    int counter = 1;
    long sizecounter = 0;

    for (int i = 0; i < ranges.Length - 1; i++)
    {
        (string, string) element = ranges[i];
        (string, string) element2 = ranges[i + 1];

        long border = Convert.ToInt64(element.Item1.Replace("0x", ""), 16) + Convert.ToInt64(element.Item2.Replace("0x", ""), 16);

        Console.WriteLine("prev: " + element.Item1);

        if (border != Convert.ToInt64(element2.Item1.Replace("0x", ""), 16))
        {
            Console.WriteLine($"\t/* HLOS {counter++} */");
            Console.WriteLine("\t{" + string.Format("0x{0:X8}", border) + ", " + string.Format("0x{0:X8}", Convert.ToInt64(element2.Item1.Replace("0x", ""), 16) - border) + ", EFI_RESOURCE_SYSTEM_MEMORY,\n" +
         "\t SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,\n" +
         "\t ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory},");
        }
        sizecounter += Convert.ToInt64(element2.Item1.Replace("0x", ""), 16) - border;
    }

    Console.WriteLine(string.Format("0x{0:X8}", sizecounter));
}