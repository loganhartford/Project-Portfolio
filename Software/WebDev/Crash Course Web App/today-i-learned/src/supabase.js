import { createClient } from "@supabase/supabase-js";

const supabaseUrl = "https://wzmnjsqqaabdckruspnv.supabase.co";
const supabaseKey =
  "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Ind6bW5qc3FxYWFiZGNrcnVzcG52Iiwicm9sZSI6ImFub24iLCJpYXQiOjE2NzMwMzk2ODEsImV4cCI6MTk4ODYxNTY4MX0.G9QPFd-M09_8DX0YgLYZUB8GjNSglcOgxc0By0OYhqU";
const supabase = createClient(supabaseUrl, supabaseKey);

export default supabase;
